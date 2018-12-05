#ifndef SEMAFORO_UI
#define SEMAFORO_UI

#include <windows.h>

// Caracteres de las esquinas
CHAR_INFO esi = { 218, 0x07 };
CHAR_INFO esd = { 191, 0x07 };
CHAR_INFO eii = { 192, 0x07 };
CHAR_INFO eid = { 217, 0x07 };

// Caracteres de los conectores
CHAR_INFO in = { 194, 0x07 };
CHAR_INFO is = { 193, 0x07 };
CHAR_INFO ii = { 195, 0x07 };
CHAR_INFO id = { 180, 0x07 };
CHAR_INFO ic = { 197, 0x07 };

// Caracteres de las lineas
CHAR_INFO vh = { 45, 0x07 };
CHAR_INFO vv = { 179, 0x07 };

// Caraceres de las luces
CHAR_INFO lae = { 219, 0x0E };
CHAR_INFO lve = { 219, 0x0A };
CHAR_INFO lre = { 219, 0x0C };

CHAR_INFO laa = { 176, 0x06 };
CHAR_INFO lva = { 176, 0x02 };
CHAR_INFO lra = { 176, 0x04 };

// Dibujo de las luces del semáforo
CHAR_INFO luz_v[] = { lve, lve, lve, lve, lve, lve };
CHAR_INFO luz_a[] = { lae, lae, lae, lae, lae, lae };
CHAR_INFO luz_r[] = { lre, lre, lre, lre, lre, lre };

// Dibujo del semáforo
CHAR_INFO g[] = {
	esi, vh, vh, vh, esd,
	vv,	lva, lva, lva, vv,
	vv,	lva, lva, lva, vv,
	ii, vh, vh, vh, id,
	vv, laa, laa, laa, vv,
	vv, laa, laa, laa, vv,
	ii, vh, vh, vh, id,
	vv, lra, lra, lra, vv,
	vv, lra, lra, lra, vv,
	eii, vh, vh, vh, eid
};

void draw_semaforo( SHORT y, SHORT x, char color )
{
	HANDLE std_out = GetStdHandle(STD_OUTPUT_HANDLE);

	SHORT y2 = y + 9;
	SHORT x2 = x + 4;

	COORD 		std_pos = { 0, 0 };

	COORD 		size_sem = { 5, 10 };
	SMALL_RECT 	rect_sem = { x, y, x2, y2};	
	
	WriteConsoleOutput( std_out, g, size_sem, std_pos, &rect_sem );

	CHAR_INFO *ptrled = 0;

	switch( color )
	{
		case 'v': y = y + 1; ptrled = luz_v; break;
		case 'a': y = y + 4; ptrled = luz_a; break;
		case 'r': y = y + 7; ptrled = luz_r; break;
	}
	
	if (ptrled == 0) return;
	
	x = x + 1;
	x2 = x + 2;
	y2 = y + 1;

	COORD 		size_led = { 3, 2 };
	SMALL_RECT 	rect_led = { x, y, x2, y2};	

	WriteConsoleOutput( std_out, ptrled, size_led, std_pos, &rect_led );	
		
}

void console_size( SHORT fils, SHORT cols )
{

	SMALL_RECT 	std_srect;
	COORD 		std_size;
	HANDLE 		std_output;

	std_srect.Top = 0;
	std_srect.Left = 0;
	std_srect.Right = cols - 1;
	std_srect.Bottom = fils - 1;

	std_size.X = cols;
    std_size.Y = fils;

    std_output = GetStdHandle(STD_OUTPUT_HANDLE);
	
	SetConsoleScreenBufferSize( std_output, std_size );
	SetConsoleWindowInfo( std_output, true, &std_srect );
	SetConsoleScreenBufferSize( std_output, std_size );

	SetConsoleActiveScreenBuffer( std_output );
}

void cursor_position( SHORT x, SHORT y)
{
	static COORD dwCursorPosition;
	dwCursorPosition.Y = y;
	dwCursorPosition.X = x;
	HANDLE std_output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition( std_output, dwCursorPosition );
}
#endif