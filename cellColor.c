struct cellColor {
	int r;
	int g;
	int b;
};

struct cellColor getColorByIndex(int index) {
	struct cellColor black = { .r=0, .g=0, .b=0 };
	struct cellColor red = { .r=104, .g=10, .b=21 };
	struct cellColor orange = { .r=145, .g=99, .b=7 };
	struct cellColor green = { .r=43, .g=66, .b=39 };
	struct cellColor blue = { .r=42, .g=43, .b=110 };
	struct cellColor purple = { .r=69, .g=24, .b=79 };
	struct cellColor colors[] = { black, red, orange, green, blue, purple };
	return colors[index % 6];
}
