/*	glX handler implementation file.
 * */
#include "include/glxh.h"

glx_handler_system_t* glx_handler_alloc(glx_handler_init_t* _init){
	glx_handler_system_t* glx_handler_system_i=(glx_handler_system_t*)calloc(1,sizeof(glx_handler_system_t));
	glx_handler_system_i->width=_init->win_length;
	glx_handler_system_i->height=_init->win_height;
	glx_handler_system_i->callback=_init->response;
	return glx_handler_system_i;
}

#define GLX_H_FAIL 0x8

unsigned char glx_handler_make_window(glx_handler_system_t* self){
	int att[]={GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None};
	if((self->dpy=XOpenDisplay(NULL))==NULL){
		return GLX_H_FAIL;
	}

	self->screen=DefaultScreen(self->dpy);
	self->root_win=RootWindow(self->dpy, self->screen);
	
	self->visual_info=glXChooseVisual(self->dpy, self->screen, att);
	
	self->xattrs.border_pixel=BlackPixel(self->dpy, self->screen);
	self->xattrs.background_pixel=WhitePixel(self->dpy, self->screen);
	self->xattrs.override_redirect=True;
	self->xattrs.colormap=XCreateColormap(self->dpy, self->root_win, self->visual_info->visual, AllocNone);
	self->xattrs.event_mask=ExposureMask|KeyPressMask;
	
	self->depth=DefaultDepth(self->dpy, self->screen);


	self->glc=glXCreateContext(self->dpy, self->visual_info,NULL, GL_TRUE);
//	self->app_win=XCreateWindow(self->dpy, self->root_win, 200, 200, self->width, self->height, 2,self->visual_info->visual, CWBackPixel|CWColormap|CWBorderPixel|CWEventMask|CWBorderPixel|CWEventMask, &self->xattrs);
	self->app_win=XCreateWindow(self->dpy, self->root_win, 100, 100, self->width, self->height, 2, self->depth, InputOutput, self->visual_info->visual, CWBackPixel|CWColormap|CWBorderPixel|CWEventMask, &self->xattrs);

	return 0x0;
}

unsigned char glx_handler_start_loop(glx_handler_system_t* self){
	XMapWindow(self->dpy, self->app_win);
	glXMakeCurrent(self->dpy, self->app_win, self->glc);
	glEnable(GL_DEPTH_TEST);

	for(;;){
		XNextEvent(self->dpy, &self->ev);
		if(self->ev.type==Expose){
			self->callback(self);
		}
	}
}

void glx_handler_destroy(glx_handler_system_t* handler){
	free(handler);
}

