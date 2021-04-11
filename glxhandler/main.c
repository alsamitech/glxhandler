#include "include/glxh.h"

unsigned char DrawMyStuff(glx_handler_system_t* hndlr){
	XGetWindowAttributes(hndlr->dpy, hndlr->app_win, &hndlr->winattr);
	glViewport(0,0,hndlr->winattr.width, hndlr->winattr.height);

	glClearColor(.7f, .7f, .7f, .7f);

	glColor3f(0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0f,0.0f,0.0f);

	glVertex3f(-0.5f, 0.0f, 0.0f);
	glVertex3f(.5f,.5f,0.0f);
	glEnd();
	glXSwapBuffers(hndlr->dpy, hndlr->app_win);
}

int main(){
	glx_handler_init_t handler_init;
	handler_init.win_height=500;
	handler_init.win_length=500;
	handler_init.response=DrawMyStuff;
	glx_handler_system_t* handler=glx_handler_alloc(&handler_init);
	glx_handler_make_window(handler);
	glx_handler_start_loop(handler);

}
