#define is_down(b) input-> buttons[b].is_down
#define pressed(b) (input-> buttons[b].is_down && input-> buttons[b].changed)
#define released(b) (!input-> buttons[b].is_down && input-> buttons[b].changed)

// NON ACELERATED VELOCITIES
float player_pos_x = 0.f;
float player_pos_y = 0.f;
// ACELERATED VELOCITIES
float player_1_p, player_1_dp, player_2_p, player_2_dp;
// ARENA VARIABLES
float arena_half_size_x = 85, arena_half_size_y = 45, arena_rectangle_grossor = 5;
float player_half_size_x = 2.5, player_half_size_y = 12;
// BALL VARIABLES
float ball_p_x, ball_p_y, ball_dp_x = 100, ball_dp_y, ball_half_size = 1;
// SCORE VARIABLES
float player_1_score, player_2_score;


enum Gamemode {
	GM_MENU,
	GM_GAMEPLAY,
};

Gamemode current_gamemode;
int hot_button;
int enemy_is_ai;

internal void simulate_player(float *p, float *dp, float ddp, float dt) {
	ddp -= *dp * 5.f;

	*p = *p + *dp * dt + ddp * dt * dt * .5f;
	*dp = *dp + ddp * dt;

	if (*p + player_half_size_y > arena_half_size_y - (arena_rectangle_grossor * 0.15f)) {
		*p = arena_half_size_y - (arena_rectangle_grossor * 0.15f) - player_half_size_y;
		*dp = 0;
	}
	else if (*p - player_half_size_y < -arena_half_size_y + (arena_rectangle_grossor * 0.15f)) {
		*p = -arena_half_size_y + (arena_rectangle_grossor * 0.15f) + player_half_size_y;
		*dp = 0;
	}
}

internal bool simulate_ball_colision(float p1x, float p1y, float hs1x, float hs1y, float p2x, float p2y, float hs2x, float hs2y) {
	return (
		p1x + hs1x > p2x - hs2x &&
		p1x - hs1x < p2x + hs2x &&
		p1y + hs1y > p2y - hs2y &&
		p1y + hs1y < p2y + hs2y);
}

internal void simulate_game(Input* input, float dt) {
	//render_background();

	clear_screen(0x0000);
	draw_empty_rect(0, 0, arena_half_size_x, arena_half_size_y, arena_rectangle_grossor, 0xfffffff, 0x00000); // ARENA

	if (current_gamemode == GM_GAMEPLAY) {


		/* NON ACELERATED VELOCITIES
		if (is_down(BUTTON_UP)) player_pos_y += speed*dt;
		if (is_down(BUTTON_DOWN)) player_pos_y -= speed * dt;
		if (pressed(BUTTON_RIGHT)) player_pos_x += speed * dt;
		if (pressed(BUTTON_LEFT)) player_pos_x -= speed * dt; */

		// PLAYER 1 - BLUE BAR
		{
			float player_1_ddp = 0.f;

			// ACELERATED VELOCITIES
			if (is_down(BUTTON_W)) player_1_ddp += 500;
			if (is_down(BUTTON_S)) player_1_ddp -= 500;

			simulate_player(&player_1_p, &player_1_dp, player_1_ddp, dt);

			draw_rect(-80, player_1_p, player_half_size_x, player_half_size_y, 0x0088ff);						// BLUE BAR

		}

		// PLAYER 2 - RED BAR
		{
			float player_2_ddp = 0.f;
			// _____________________________________________________________________AI____________________________
			if (!enemy_is_ai) {
				// ACELERATED VELOCITIES
				if (is_down(BUTTON_UP)) player_2_ddp += 500;
				if (is_down(BUTTON_DOWN)) player_2_ddp -= 500;
			}
			else {
				player_2_ddp = (ball_p_y - player_2_p) * 100;
				if (player_2_ddp > 1300) player_2_ddp = 1300;
				if (player_2_ddp < -1300) player_2_ddp = -1300;
			}

			simulate_player(&player_2_p, &player_2_dp, player_2_ddp, dt);

			draw_rect(80, player_2_p, player_half_size_x, player_half_size_y, 0xff00000);						// RED BAR

		}

		// Simulate BALL
		{
			ball_p_x += ball_dp_x * dt;
			ball_p_y += ball_dp_y * dt;


			if (simulate_ball_colision(ball_p_x, ball_p_y, ball_half_size, ball_half_size, -80, player_1_p, player_half_size_x, player_half_size_y)) {
				ball_p_x = -80 + player_half_size_x + ball_half_size;
				ball_dp_x *= -1;
				ball_dp_y = (ball_p_y - player_1_p) * 2 + player_1_dp * 0.75f;
			}
			else if (simulate_ball_colision(ball_p_x, ball_p_y, ball_half_size, ball_half_size, 80, player_2_p, player_half_size_x, player_half_size_y)) {
				ball_p_x = 80 - player_half_size_x - ball_half_size;
				ball_dp_x *= -1;
				ball_dp_y = (ball_p_y - player_2_p) * 2 + player_2_dp * 0.75f;
			}

			if (ball_p_y + ball_half_size > arena_half_size_y - (arena_rectangle_grossor * 0.15f)) {
				ball_p_y = arena_half_size_y - (arena_rectangle_grossor * 0.15f) - ball_half_size;
				ball_dp_y *= -1;
			}
			else if (ball_p_y - ball_half_size < -arena_half_size_y + (arena_rectangle_grossor * 0.15f)) {
				ball_p_y = -arena_half_size_y + (arena_rectangle_grossor * 0.15f) + ball_half_size;
				ball_dp_y *= -1;
			}

			if (ball_p_x + ball_half_size > arena_half_size_x - (arena_rectangle_grossor * 0.15f)) {
				ball_p_x = 0;
				ball_p_y = 0;
				ball_dp_y = 0;
				ball_dp_x *= -1;
				player_1_score++;
			}
			else if (ball_p_x - ball_half_size < -arena_half_size_x + (arena_rectangle_grossor * 0.15f)) {
				ball_p_x = 0;
				ball_p_y = 0;
				ball_dp_y = 0;
				ball_dp_x *= -1;
				player_2_score++;
			}

			draw_rect(ball_p_x, ball_p_y, ball_half_size, 1, 0xffffff);							// BALL

		}

		// SCORE
		{
			draw_number(player_1_score, -10, 40, 1.f, 0x0088ff);		// BLUE BAR SCORE
			draw_number(player_2_score, 10, 40, 1.f, 0xff0000);		// RED BAR SCORE
		}
	}
	else {

		if (pressed(BUTTON_LEFT) || pressed(BUTTON_RIGHT)) {
			hot_button = !hot_button;
		}
		if (pressed(BUTTON_ENTER)) {
			current_gamemode = GM_GAMEPLAY;
			enemy_is_ai = hot_button ? 0 : 1;
		}
		if (hot_button == 0) {

			draw_text("SINGLE PLAYER",-40, 20, 0.5, 0xff88);

			draw_empty_rect(20, 0, 10, 10, 3, 0xffffff, 0x0000);
			draw_rect(20 + 4, 0 + 1.5 * 2.f, 1, 3, 0xff88);
			draw_rect(20 - 4, 0 - 1.5 * 2.f, 1, 3, 0xff88);
			draw_rect(20 - 4, 0 + 2.8 * 2.f, 1, 0.5, 0xff88);
			draw_rect(20 + 4, 0 - 2.8 * 2.f, 1, 0.5, 0xff88);
			draw_rect(20, 0 - 3 * 2.f, 5, 0.25, 0xff88);
			draw_rect(20, 0 + 3 * 2.f, 5, 0.25, 0xff88);
			draw_rect(20, 0, 5, 0.10, 0xff88);
			draw_rect(-20, 0, 10, 10, 0xffffff);
			draw_rect(-20, 0, 1, 6, 0xff88);
		}
		else {
			draw_text("MULTIPLAYER", 2, 20, 0.5, 0xff88);
			draw_rect(20, 0, 10, 10, 0xffffff);
			draw_empty_rect(-20, 0, 10, 10, 3, 0xffffff,0x00000);
			draw_rect(-20, 0, 1, 6, 0xff88);
			draw_rect(20 + 4, 0 + 1.5 * 2.f, 1, 3, 0xff88);
			draw_rect(20 - 4, 0 - 1.5 * 2.f, 1, 3, 0xff88);
			draw_rect(20 - 4, 0 + 2.8 * 2.f, 1, 0.5, 0xff88);
			draw_rect(20 + 4, 0 - 2.8 * 2.f, 1, 0.5, 0xff88);
			draw_rect(20, 0 - 3 * 2.f, 5, 0.25, 0xff88);
			draw_rect(20, 0 + 3 * 2.f, 5, 0.25, 0xff88);
			draw_rect(20, 0, 5, 0.10, 0xff88);
			
		}
		draw_text("PONG: THE GAME!", -50, 40, 1.1, 0xfffff);
		draw_text("SERGIO MIGUEZ APARICIO", 40, -42, 0.2, 0xff88);
	}
}