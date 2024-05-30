#include "../headers/main.h"


bool isRayFacingUp(float angle){
    return (!isRayFacingDown(angle));
}

bool isRayFacingDown(float angle){
    return (angle > 0 && angle < PI);
}

bool isRayFacingRight(float angle){
    return (angle < 0.5 * PI || angle > 1.5 * PI);
}

bool isRayFacingLeft(float angle){
    return (!isRayFacingRight(angle));
}

float calculateDistance(float x1, float y1, float x2, float y2){
    return (sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2)));
}