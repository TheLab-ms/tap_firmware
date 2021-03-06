/*
 * Plasma demo for the TAP (Technology Access Platform)
 *
 * Copyright (C) 2016 TheLab.ms
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 */

#include "main.h"

#define GLOBAL_Q 8
#include "QmathLib.h"

#define M_PI 3.14159265358979323846

unsigned int frame_num;

void setup(void)
{
	// This code is invoked once to initialize the demo...
	frame_num = 0;
}

void loop(void)
{
	unsigned int row, col;
    unsigned int col_offset = state.x_address * 8;  //state.address used to find out your address.
    unsigned int row_offset = state.y_address * 8;

	_q u_k = _Q(0.5f);
	_q u_time = _Q((float)(state.frame_sync * 128) / UINT16_MAX);
	for (row = 0; row < NUM_ROWS; row++)
	{
		for (col = 0; col < NUM_COLS; col++)
		{
			_q v = _Q(0.0f);
			_q x = _Qmpy(_Q(row + row_offset), u_k) - _Qdiv2(u_k);
			_q y = _Qmpy(_Q(col + col_offset), u_k) - _Qdiv2(u_k);
			v += _Qsin((x + u_time));
			v += _Qsin(_Qdiv2(y + u_time));
			v += _Qsin(_Qdiv2(x + y + u_time));
			x += _Qmpy(_Qdiv2(u_k), _Qsin(_Qdiv(u_time, _Q(3.0f))));
			y += _Qmpy(_Qdiv2(u_k), _Qcos(_Qdiv2(u_time)));
			v += _Qsin(_Qsqrt(_Qmpy(x, x) + _Qmpy(y,y) + _Q(1.0f)) + u_time);
			v = _Qdiv2(v);

			display_buffer[row][(col * COL_SIZE) + 0] = 1 * 20;
			display_buffer[row][(col * COL_SIZE) + 1] = _Qint(_Qmpy(_Qsin(_Qmpy(_Q(M_PI),v)), 20));
			display_buffer[row][(col * COL_SIZE) + 2] = _Qint(_Qmpy(_Qcos(_Qmpy(_Q(M_PI),v)), 20));
		}
	}
}
