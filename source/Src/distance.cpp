#include "../Inc/distance.hpp"

Mat measure_distance(Rect rect)
{
	auto begin = chrono::high_resolution_clock::now();
	Point2f tl = rect.tl();
	Point2f br = rect.br();
	vector<Point2f> points{tl, Point2f(br.x, tl.y), br, Point2f(tl.x, br.y)};
	Mat rvec, tvec;
	solvePnP(ore_vertices, points, cameraMatrix, zeros, rvec, tvec);
	Mat rotM;
	Rodrigues(rvec, rotM);
	Mat rotInv = rotM.inv();
	Mat pos = -rotInv * tvec;
	return pos;
	auto end = chrono::high_resolution_clock::now();
	auto interval = chrono::duration_cast<chrono::milliseconds>(end - begin);
	cout << __func__ << " cost: " << interval.count() << endl;
}

Mat measure_distance_rotated(RotatedRect rect)
{
	vector<Point2f> vertices;
	rect.points(vertices);
	Mat rvec, tvec;
	solvePnP(ore_vertices, vertices, cameraMatrix, zeros, rvec, tvec);
	Mat rotM;
	Rodrigues(rvec, rotM);
	Mat rotInv = rotM.inv();
	Mat pos = -rotInv * tvec;
	return pos;
}