#include <stdio.h>
#include <stdlib.h>
#include <linux/input.h>

#include "omb_common.h"
#include "omb_log.h"
#include "omb_freetype.h"
#include "omb_framebuffer.h"
#include "omb_utils.h"
#include "omb_menu.h"

static int omb_timer_enabled;
static int omb_current_timer;

void omb_draw_header()
{
	char tmp[255];
	sprintf(tmp, "%s %s", OMB_DISPLAY_NAME, OMB_APP_VERION);
	omb_render_symbol(OMB_SYMBOL_LOGO,
		OMB_HEADER_X,
		OMB_HEADER_Y - 25,
		400,
		OMB_HEADER_COLOR,
		OMB_HEADER_FONT_SIZE,
		OMB_TEXT_ALIGN_LEFT);
	
	omb_render_text(tmp,
		OMB_HEADER_X + 45,
		OMB_HEADER_Y,
		400,
		OMB_HEADER_COLOR,
		OMB_HEADER_FONT_SIZE,
		OMB_TEXT_ALIGN_LEFT);
}

void omb_draw_timer()
{
	if (omb_timer_enabled) {
		char tmp[255];
		sprintf(tmp, "%d", omb_current_timer);
		omb_render_text(tmp,
			omb_get_screen_width() - (400 + OMB_TIMER_RIGHT_MARGIN),
			OMB_TIMER_Y,
			400,
			OMB_TIMER_COLOR,
			OMB_TIMER_FONT_SIZE,
			OMB_TEXT_ALIGN_RIGHT);
	}
}

void omb_refresh_gui()
{
	omb_clear_screen();
	omb_draw_header();
	omb_draw_timer();
	omb_menu_render();
	omb_blit();
}

int omb_show_menu()
{
	struct timeval start, end;
	
	if (omb_open_framebuffer() == OMB_ERROR)
		return OMB_ERROR;
	
	if (omb_init_freetype() == OMB_ERROR)
		return OMB_ERROR;
	
	if (omb_input_open() == OMB_ERROR)
		return OMB_ERROR;
	
	omb_timer_enabled = 1;
	omb_current_timer = OMB_DEFAULT_TIMER;
	gettimeofday(&start, NULL);
	
	omb_refresh_gui();
	
	for(;;) {
		usleep(20000);
		int need_refresh_gui = 0;
		int code = omb_input_get_code();
		if (code == KEY_OK)
			break;
		else if (code == KEY_UP) {
			omb_menu_prev();
			omb_utils_update_background(omb_menu_get_selected());
			need_refresh_gui = 1;
			omb_timer_enabled = 0;
		}
		else if (code == KEY_DOWN) {
			omb_menu_next();
			omb_utils_update_background(omb_menu_get_selected());
			need_refresh_gui = 1;
			omb_timer_enabled = 0;
		}
		
		if (omb_timer_enabled) {
			long mtime, seconds, useconds;
			gettimeofday(&end, NULL);
			
			seconds  = end.tv_sec  - start.tv_sec;
			useconds = end.tv_usec - start.tv_usec;

			mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;
			int last_value = omb_current_timer;
			omb_current_timer = OMB_DEFAULT_TIMER - (mtime / 1000);
			
			if (omb_current_timer != last_value)
				need_refresh_gui = 1;
		}
		
		if (need_refresh_gui)
			omb_refresh_gui();
		
		
		if (omb_current_timer == 0)
			break;
	}

	omb_clear_screen();
	omb_blit();
	
	omb_input_close();
	omb_deinit_freetype();
	omb_close_framebuffer();
}

int main(int argc, char *argv[]) 
{
	int is_rebooting = 0;
	if (argc > 1) {
		omb_utils_sysvinit(NULL, argv[1]);
	}
	else {
		omb_utils_init_system();
		omb_device_item *item = NULL;
		omb_device_item *items = NULL;
		char *selected = NULL;
		if (omb_utils_find_and_mount() == OMB_SUCCESS) {
			items = omb_utils_get_images();
			omb_menu_set(items);
			selected = omb_utils_read(OMB_SETTINGS_SELECTED);
			if (selected != NULL)
				omb_menu_set_selected(selected);
		
			item = omb_menu_get_selected();
			omb_utils_update_background(item);
		}
		int force = omb_utils_read_int(OMB_SETTINGS_FORCE);
		if (!force) {
			omb_utils_load_modules(item);
			omb_utils_backup_kernel(item);
	
			omb_show_menu();
		}
		else {
			omb_utils_save_int(OMB_SETTINGS_FORCE, 0);
		}
	
		item = omb_menu_get_selected();
		if (item) {
			if (strcmp(selected, item->identifier) != 0) {
				omb_utils_restore_kernel(item);
				omb_utils_save(OMB_SETTINGS_SELECTED, item->identifier);
				omb_utils_save_int(OMB_SETTINGS_FORCE, 1);
				omb_utils_reboot();
				is_rebooting = 1;
			}
		}
		
		if (!is_rebooting)
			omb_utils_sysvinit(item, NULL);
	
		if (items) omb_utils_free_items(items);
		if (selected) free(selected);
	}
	
	return OMB_SUCCESS;
}

