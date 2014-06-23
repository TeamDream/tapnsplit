
/*
rectangle numeration order:
...left screen border | 3 | 2 | 1 | 0 | right screen border...
*/

class RectTrajectory {
protected:
	int rects_n;
public:
	RectTrajectory(int _row_width) : rects_n(_row_width) {};
	virtual int calcPosition() = 0;// yeah, it's pretty simple
};

class RandTrajectory :public RectTrajectory{
protected:
	int rects_n;
public:
	RandTrajectory(int _row_width) :RectTrajectory(_row_width) {};
	int calcPosition() { return rand() % rects_n; }
};

class CrossTrajectory : public RectTrajectory {
public:
	CrossTrajectory(int _row_width) : RectTrajectory(_row_width),
									  reverse(false), rect_count(-1) {}
	int calcPosition() {

		if (rect_count >= rects_n - 1) 
			reverse = true; 
		else if (rect_count <= 0)
			reverse = false;
		 
		reverse ? rect_count-- : rect_count++;	
		return rect_count;

	}
private:
	bool reverse;
	int rect_count;
};

class ChessTrajectory : public RectTrajectory {
public:
	ChessTrajectory(int _row_width) : RectTrajectory(_row_width),
		start_pos(1), rect_count(0) {}
	
	int calcPosition() {

		if (rect_count % 10 == 0) {
			start_pos = rand() % (rects_n - 1) + 1; //we need only [1...rects_n) start positions
		}

		rect_count++;

		return start_pos - rect_count%2;
	}

private:
	int start_pos;
	int rect_count;
};