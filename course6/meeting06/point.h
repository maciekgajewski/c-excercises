struct Point
{
	int x;
	int y;
	int length() const;
};

inline int Point::length() const { return x + y; }
