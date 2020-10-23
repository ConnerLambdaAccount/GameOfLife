struct cellColor {
	int r;
	int g;
	int b;
};

struct cellColor getColorByIndex(int index) {
	struct cellColor black = { .r=0, .g=0, .b=0 };
	struct cellColor red = { .r=255, .g=0, .b=0 };
	struct cellColor colors[] = { black, red };
	return colors[index % 2];
}
