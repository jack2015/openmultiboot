#ifndef _OMB_COMMON_H_
#define _OMB_COMMON_H_

#define OMB_SUCCESS 0
#define OMB_ERROR -1

#define OMB_DEVICES_DIR "/dev"
#define OMB_FB_DEVICE "/dev/fb/0"
#define OMB_INPUT_DEVICE "/dev/input/event0"
#define OMB_VIDEO_DEVICE "/dev/dvb/adapter0/video0"
#define OMB_KERNEL_MTD "/dev/mtd2"
#define OMB_MAIN_DIR "/media"
#define OMB_DATA_DIR "open-multiboot"
#define OMB_SCREEN_WIDTH 1280
#define OMB_SCREEN_HEIGHT 720
#define OMB_SCREEN_BPP 32
#define OMB_APP_NAME "open-multiboot"
#define OMB_APP_VERION "0.1"
#define OMB_DISPLAY_NAME "openMultiboot"
#define OMB_DEFAULT_TIMER 5
#define OMB_SHOWIFRAME_BIN "/usr/bin/showiframe"
#define OMB_MDEV_BIN "/etc/init.d/mdev"
#define OMB_MODUTILS_BIN "/etc/init.d/modutils.sh"
#define OMB_SYSVINIT_BIN "/sbin/init.sysvinit"
#define OMB_CHROOT_BIN "/usr/sbin/chroot"
#define OMB_NANDDUMP_BIN "/usr/sbin/nanddump"
#define OMB_NANDWRITE_BIN "/usr/sbin/nandwrite"
#define OMB_FLASHERASE_BIN "/usr/sbin/flash_erase"

#define OMB_MENU_ITEM_RADIUS 10
#define OMB_MENU_ITEM_HEIGHT 80
#define OMB_MENU_ITEM_WIDTH 800
#define OMB_MENU_ITEM_COLOR 0xFA404040
#define OMB_MENU_ITEM_SELECTED_COLOR 0xFA202020
#define OMB_MENU_ITEM_TEXT_COLOR 0xFFFFFFFF
#define OMB_MENU_ITEM_TEXT_BOTTON_MARGIN 24
#define OMB_MENU_ITEM_TEXT_FONT_SIZE 34
#define OMB_MENU_BOX_RADIUS 10
#define OMB_MENU_BOX_MARGIN 6
#define OMB_MENU_BOX_COLOR 0xE0202020
#define OMB_MENU_MAX_ITEMS 5
#define OMB_MENU_ARROWS_SIZE 120
#define OMB_MENU_ARROWS_COLOR 0xFA202020

#define OMB_HEADER_X 20
#define OMB_HEADER_Y 40
#define OMB_HEADER_FONT_SIZE 24
#define OMB_HEADER_COLOR 0xFFFFFFFF

#define OMB_TIMER_RIGHT_MARGIN 20
#define OMB_TIMER_Y 50
#define OMB_TIMER_FONT_SIZE 34
#define OMB_TIMER_COLOR 0xFFFFFFFF

#endif // _OMB_COMMON_H_