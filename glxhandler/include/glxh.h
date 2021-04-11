#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>		// Linux-Specific

// libX11 header files
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>

// OpenGL Headers
#include <GL/gl.h>
#include <GL/glx.h>

typedef unsigned char (*glx_handler_resp) (void*);

typedef struct{
	int win_length;
	int win_height;	
	glx_handler_resp response;
}glx_handler_init_t;

typedef struct{
	glx_handler_resp callback;
	Display* dpy;
	int screen;
	Window app_win, root_win;
	XEvent ev;
	XSetWindowAttributes xattrs;
	XWindowAttributes winattr;
	XVisualInfo* visual_info;
	unsigned int depth;
	int width, height;
	GLXContext glc;

}glx_handler_system_t;


glx_handler_system_t* glx_handler_alloc(glx_handler_init_t* _init);
void glx_handler_destroy(glx_handler_system_t* handler);
