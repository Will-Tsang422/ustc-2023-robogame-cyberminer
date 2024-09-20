#include "../Inc/perspective.hpp"

Mat transform(Mat img, Rect rect)
{
	Point2f tl = rect.tl();
	Point2f br = rect.br();
	vector<Point2f> points{ tl, Point2f(br.x, tl.y), br, Point2f(tl.x, br.y) };
	Point2f tl_dst((img.cols - rect.width) / 2, (img.rows - rect.height) / 2);
	Point2f tr_dst((img.cols + rect.width) / 2, (img.rows - rect.height) / 2);
	Point2f br_dst((img.cols + rect.width) / 2, (img.rows + rect.height) / 2);
	Point2f bl_dst((img.cols - rect.width) / 2, (img.rows + rect.height) / 2);
	vector<Point2f> dst{ tl_dst, tr_dst, br_dst, bl_dst };
	Mat M = getPerspectiveTransform(points, dst);
	Mat dst_img;
	warpPerspective(img, dst_img, M, img.size());
	return dst_img;
}