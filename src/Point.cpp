//
// Saar Shtalryd 307838854 & Itay Oktan 203036512
//

#include "Point.h"

/**
 * Point constructor.
 * @param pointX the X axis value.
 * @param pointY the Y axis value.
 * @return nothing.
 */
Point::Point(int pointX, int pointY) {
    x = pointX;
    y = pointY;
}

/**
 * getX.
 * @return the X axis value of the point.
 */
int Point::getX() const {
    return x;
}

/**
 * getY
 * @return the Y axis value of the point.
 */
int Point::getY() const {
    return y;
}

/**
 * operator== overload.
 * @param other the point is to be compared with the current one.
 * @return whether the points are equal or not.
 */
bool Point::operator==(const Point& other) {
    return (x==other.getX() && y==other.getY());
}

/**
 * operator!= overload.
 * @param other the point is to be compared with the current one.
 * @return whether the points are not equal.
 */
bool Point::operator!=(const Point& other) {
    return !(x==other.getX() && y==other.getY());
}

/**
 * operator<< overload.
 * @param os the ostream that is to be changed.
 * @param p the point that is to be printed.
 * @return the changed ostream.
 */
ostream& operator<<(std::ostream& os, const Point& p) {
    return os << "(" << p.x << "," << p.y << ")";
}