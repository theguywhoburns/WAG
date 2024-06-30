#include <math.h>
#include <WAG/util/wmath.h>


double wsin(double x) {
	return sin(x);
}

double wcos(double x) {
	return cos(x);
}

double wtan(double x) {
	return tan(x);
}

double wctg(double x) {
	return 1.0f / tan(x);
}

double wacos(double x) {
	return acos(x);
}

double wasin(double x) {
	return asin(x);
}

double watan(double x) {
	return atan(x);
}

double wactg(double x) {
	return 1.0f / atan(x);
}


double wsqrt(double x) {
	return sqrt(x);
}

double wabs(double x) {
	return fabs(x);
}

double wfloor(double x) {
	return floor(x);
}

double wceil(double x) {
	return ceil(x);
}

double wlog2(double x) {
	return log2(x);
}

double wpow(double x, double y) {
	return pow(x, y);
}


//TODO:
int32_t wrandom() {
 return 0;
}

//TODO:
double wfrandom() {
	return 0.0f;
}

//TODO:
double wfrandom_range(double min, double max) {
	return min - max;
}
