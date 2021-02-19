

internal void clear_screen(u32 color) {
	unsigned int* pixel = (u32*)render_state.memory;
	for (int y = 0; y < render_state.height; y++) {
		for (int x = 0; x < render_state.width; x++) {
			*pixel++ = color;
		}
	}
}


internal void draw_rect_in_pixels(int x0, int y0, int x1, int y1, unsigned int color) {

	x0 = clamp(0, x0, render_state.width);
	x1 = clamp(0, x1, render_state.width);
	y0 = clamp(0, y0, render_state.height);
	y1 = clamp(0, y1, render_state.height);

	for (int y = y0; y < y1; y++) {
		u32* pixel = (u32*)render_state.memory + x0 + y*render_state.width;
		for (int x = x0; x < x1; x++) {
			*pixel++ = color;
		}
	}

}

global_variable float rende_scaler = 0.01f;

internal void draw_rect(float x, float y, float half_size_x, float half_size_y, u32 color) {

	x *= render_state.height * rende_scaler;
	y *= render_state.height * rende_scaler;
	half_size_x *= render_state.height * rende_scaler;
	half_size_y *= render_state.height * rende_scaler;

	x += render_state.width/ 2;
	y += render_state.height/ 2;
	// change to pixels
	int x0 = x - half_size_x;
	int x1 = x + half_size_x;
	int y0 = y - half_size_y;
	int y1 = y + half_size_y;

	draw_rect_in_pixels(x0, y0, x1, y1, color);
}

internal void draw_empty_rect(float x, float y, float half_size_x, float half_size_y, int grossor, u32 color, u32 insideColor) {

	x *= render_state.height * rende_scaler;
	y *= render_state.height * rende_scaler;
	half_size_x *= render_state.height * rende_scaler;
	half_size_y *= render_state.height * rende_scaler;

	x += render_state.width / 2;
	y += render_state.height / 2;
	// change to pixels
	int x0 = x - half_size_x;
	int x1 = x + half_size_x;
	int y0 = y - half_size_y;
	int y1 = y + half_size_y;

	// inner
	int xi0 = x0 + grossor;
	int xi1 = x1 - grossor;
	int yi0 = y0 + grossor;
	int yi1 = y1 - grossor;

	draw_rect_in_pixels(x0, y0, x1, y1, color);
	draw_rect_in_pixels(xi0, yi0, xi1, yi1, insideColor);
}



internal void draw_text(const char *text, float x, float y, float size, u32 color) {
	float half_size = size * 0.5f;
	float original_y = y;

	while (*text) {
		if (*text != 32) {
			const char** letter;
			if (*text == 46) letter = letters[26];
			else if (*text == 58) letter = letters[27];
			else if (*text == 33) letter = letters[28];
			else if (*text == 48) letter = letters[29];
			else if (*text == 49) letter = letters[30];
			else if (*text == 50) letter = letters[31];
			else if (*text == 51) letter = letters[32];
			else if (*text == 52) letter = letters[33];
			else if (*text == 53) letter = letters[34];
			else if (*text == 54) letter = letters[35];
			else if (*text == 55) letter = letters[36];
			else if (*text == 56) letter = letters[37];
			else if (*text == 57) letter = letters[38];
			else if (*text == 45) letter = letters[39];
			else letter = letters[*text - 'A'];
			float original_x = x;
			for (int i = 0; i < 7; i++) {
				const char* row = letter[i];
				while (*row) {
					if (*row == '0') {
						draw_rect(x, y, half_size, half_size, color);
					}
					x += size;
					row++;
				}
				y -= size;
				x = original_x;
			}
		}
		text++;
		x += size * 6.5f;
		y = original_y;
	}
	

}

internal void draw_number(int number, float x, float y, float size, u32 color) {
	float half_size = size * .5f;
	bool drew_number = false;
	while (number || !drew_number)
	{
		drew_number = true;
		int digit = number % 10;
		number = number / 10; 
		switch (digit)
		{
		case 0: {
			draw_rect(x - size, y, half_size, 2.5f * size, color);
			draw_rect(x + size, y, half_size, 2.5f * size, color);
			draw_rect(x, y - size * 2.f, half_size, half_size, color);
			draw_rect(x, y + size * 2.f, half_size, half_size, color);
			x -= size * 4.f;
			break;
		}
		case 1: {
			draw_rect(x + size, y, half_size, 2.5f * size, color);
			x -= size * 2.f;
			break;
		}
		case 2: {
			draw_rect(x, y + size * 2.f, 1.5f * size, half_size, color);
			draw_rect(x, y, 1.5f * size, half_size, color);
			draw_rect(x, y - size * 2.f, 1.5f * size, half_size, color);
			draw_rect(x + size, y + size, half_size, half_size, color);
			draw_rect(x - size, y - size, half_size, half_size, color);
			x -= size * 4.f;
			break;
		}
		case 3: {
			draw_rect(x, y + size * 2.f, 1.5f * size, half_size, color);
			draw_rect(x, y, 1.5f * size, half_size, color);
			draw_rect(x + size, y + size, half_size, half_size, color);
			draw_rect(x + size, y - size, half_size, 1.5 * size, color);
			draw_rect(x, y - size * 2.f, 1.5f * size, half_size, color);
			x -= size * 4.f;
			break;
		}
		case 4: {
			draw_rect(x, y, half_size, half_size, color);
			draw_rect(x - size, y + size, half_size, 1.5f * size, color);
			draw_rect(x + size, y, half_size, 2.5 * size, color);
			x -= size * 4.f;
			break;
		}
		case 5: {
			draw_rect(x, y + size * 2.f, 1.5f * size, half_size, color);
			draw_rect(x, y, 1.5f * size, half_size, color);
			draw_rect(x, y - size * 2.f, 1.5f * size, half_size, color);
			draw_rect(x - size, y + size, half_size, half_size, color);
			draw_rect(x + size, y - size, half_size, half_size, color);
			x -= size * 4.f;
			break;
		}

		case 6: {
			draw_rect(x, y + size * 2.f, 1.5f * size, half_size, color);
			draw_rect(x, y, 1.5f * size, half_size, color);
			draw_rect(x, y - size * 2.f, 1.5f * size, half_size, color);
			draw_rect(x + size, y + size, half_size, half_size, color);
			draw_rect(x - size, y - size, half_size, half_size, color);
			draw_rect(x + size, y - size, half_size, half_size, color);
			x -= size * 4.f;
			break;
		}
		case 7: {
			draw_rect(x, y + size * 2.f, 1.5f * size, half_size, color);
			draw_rect(x + size, y, half_size, 2.5f * size, color);
			x -= size * 4.f;
			break;
		}
		case 8: {
			draw_rect(x, y + size * 2.f, 1.5f * size, half_size, color);
			draw_rect(x, y, 1.5f * size, half_size, color);
			draw_rect(x, y - size * 2.f, 1.5f * size, half_size, color);
			draw_rect(x + size, y + size, half_size, half_size, color);
			draw_rect(x - size, y - size, half_size, half_size, color);
			draw_rect(x + size, y - size, half_size, half_size, color);
			draw_rect(x - size, y + size, half_size, half_size, color);
			x -= size * 4.f;
			break;
		}
		case 9: {
			draw_rect(x, y + size * 2.f, 1.5f * size, half_size, color);
			draw_rect(x, y, 1.5f * size, half_size, color);
			draw_rect(x + size, y + size, half_size, half_size, color);
			draw_rect(x + size, y - size, half_size, 1.5 * size, color);
			draw_rect(x - size, y + size, half_size, half_size, color);
			x -= size * 4.f;
			break;
		}

		default:
			break;
		}
	}
}