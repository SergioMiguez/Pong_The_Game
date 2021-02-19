struct Button_State
{
	bool is_down = false;
	bool changed = true;
};


enum {
	BUTTON_UP,
	BUTTON_DOWN,

	BUTTON_LEFT,
	BUTTON_RIGHT,
	BUTTON_ENTER,

	BUTTON_W,
	BUTTON_S,

	BUTTON_COUNT, //
};

struct Input
{
	Button_State buttons[BUTTON_COUNT];
};