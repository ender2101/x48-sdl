
	SDLMessageBox(300,200,errinit_title,errinit_text,0xf0e0c0c0,0xff000000,0);
	
	// Benchmarks
	t1 = SDL_GetTicks();
	for(i=0;i<1000;i++)
	{
		SDL_LockSurface(sdlscreen);
		SDL_UnlockSurface(sdlscreen);
	}
	t2 = SDL_GetTicks();
	printf("1000 Lock/Unlock: %d\n",t2-t1);
	t1 = SDL_GetTicks();
	for(i=0;i<10;i++)
	{
		SDL_Delay(1);
	}
	t2 = SDL_GetTicks();
	printf("10 SDL_Delay: %d\n",t2-t1);
	t1 = SDL_GetTicks();
	for(i=0;i<1000;i++)
	{
		usleep(800);
	}
	t2 = SDL_GetTicks();
	printf("1000 usleep(10): %d\n",t2-t1);	
	
	t1 = SDL_GetTicks();
	for(i=0;i<10;i++)
	{
		printf("%d ",i);
		SDL_UpdateRect(sdlscreen,0,0,0,0);
	}
	t2 = SDL_GetTicks();
	printf("10 UpdateRect: %d\n",t2-t1);
	t1 = SDL_GetTicks();
	for(i=0;i<10;i++)
	{
		printf("%d ",i);
		SDL_UpdateRect(sdlscreen,0,0,262,128);
	}
	t2 = SDL_GetTicks();
	printf("10 screenlike UpdateRect: %d\n",t2-t1);
	
	
	SDLMessageBox(300,200,errinit_title,errinit_text,0xf0e0c0c0,0xff000000,0);
	