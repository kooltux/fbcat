#include <Ecore.h>
#include <Elementary.h>

#include <stdio.h>
#include <stdlib.h>


 // window close callback
static void on_win_del (void *data, Evas_Object *obj, void *event_info)
{
	elm_exit ();
}

static Eina_Bool on_stdin_change (void *data, Ecore_Fd_Handler *handler)
{
	Evas_Object *label = (Evas_Object *)data;
	char buffer[1024];
	size_t nbytes;
	int fd;

	if (ecore_main_fd_handler_active_get (handler, ECORE_FD_ERROR)) {
		fprintf(stderr,"An error has occured. Quitting.\n");
		elm_object_text_set (label, "");
		elm_exit ();
		return ECORE_CALLBACK_CANCEL;
	}

	fd = ecore_main_fd_handler_fd_get (handler);
	nbytes = read (fd, buffer, sizeof(buffer));
	if (nbytes == 0) {
		elm_object_text_set (label, "");
		elm_exit ();
		return ECORE_CALLBACK_CANCEL;
	}

	buffer[nbytes]='\0';
	elm_object_text_set (label, buffer);

	return ECORE_CALLBACK_RENEW;
}

int elm_main (int argc, char **argv)
{
	Evas_Object *window, *bg, *box, *label;
	Ecore_Fd_Handler *handler;

	window = elm_win_add (NULL, "main", ELM_WIN_BASIC);
	elm_win_title_set (window, "EFL Framebuffer test");

	bg = elm_bg_add (window);
	box = elm_box_add (window);
	label = elm_label_add (window);

	evas_object_size_hint_min_set (bg, 848, 480);
	evas_object_size_hint_max_set (bg, 848, 480);
	elm_bg_color_set (bg, 255, 255, 255);

	elm_win_resize_object_add (window, bg);
	elm_win_resize_object_add (window, box);
	elm_box_pack_end (box, label);

	evas_object_smart_callback_add (window, "delete,request", on_win_del, NULL);

	evas_object_show (bg);
	evas_object_show (label);
	evas_object_show (box);
	evas_object_show (window);

	elm_object_text_set (label, "<font=Sans color=blue font_size=24>Default</font> text");
	handler = ecore_main_fd_handler_add (STDIN_FILENO,
	                                     ECORE_FD_READ | ECORE_FD_ERROR,
	                                     on_stdin_change,
	                                     label, NULL, NULL);

	elm_run ();

	return 0;
}
ELM_MAIN();
