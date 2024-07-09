#include "cub3d.h"

/*
=> RAYCASTING BASCIS
Use trigonometric functions to calculate the direction vector of each ray:
    rayDirX = cos(playerAngle);
    rayDirY = sin(playerAngle);

=> HORIZONTAL RAYCASTING

1. Determining Ray Direction:
Determine if the ray is facing up (rayDirY < 0) or down (rayDirY > 0)

2. Grid Intersection: 
Calculate the position of the first horizontal grid line (firstHorizY)
    if (rayDirY < 0)
        firstHorizY = (playerY / 64) * 64;
    else
        firstHorizY = ((playerY / 64) * 64) + 64;

note: you round the ray's Y position to the nearest multiple of 64
      either dividing by 64 (shifting right by 6 bits), and then multiplying back or adjusting slightly for precision

3. Calculating Distance to Wall: 
Determine the X coordinate where the ray intersects this line
    horizHitX = playerX + (firstHorizY - playerY) / tan(playerAngle);

note: you calculate the X coordinate by adding the distance between the player and the Y position of the ray, 
      multiplied by the inverse of the tangent of the ray's angle, to the player's X position

4. Check the map at (horizHitX, firstHorizY) to see if there's a wall (map[horizHitX / 64][firstHorizY / 64] == 1).

5. Incremental Checks:
Incrementally check subsequent horizontal grid lines (nextHorizY) until a wall is hit or the map boundary is exceeded.

=> VERTICAL RAYCASTING

1. Determining Ray Direction:
Determine if the ray is facing left (rayDirX < 0) or right (rayDirX > 0).

2. Grid Intersection:
Calculate the position of the first vertical grid line (firstVertX)
    if (rayDirX > 0)
        firstVertX = ((playerX / 64) * 64) + 64;
    else
        firstVertX = (playerX / 64) * 64;

3. Calculating Distance to Wall:
Calculate the Y coordinate where the ray intersects this line
    vertHitY = playerY + (firstVertX - playerX) * tan(playerAngle);

4. Check the map at (firstVertX, vertHitY) to see if there's a wall (map[firstVertX / 64][vertHitY / 64] == 1).

5. Incremental Checks:
Incrementally check subsequent vertical grid lines (nextVertX) until a wall is hit or the map boundary is exceeded.

=> COLLISION DETECTION
1. Distance Calculation:
Use the Pythagorean theorem to calculate the distance from the player to each wall hit:
horizDistance = sqrt(pow(horizHitX - playerX, 2) + pow(firstHorizY - playerY, 2));
vertDistance = sqrt(pow(firstVertX - playerX, 2) + pow(vertHitY - playerY, 2));

2. Choosing the Closest Wall:
Compare horizDistance and vertDistance to determine which ray hit the wall first (closer distance).

=> RENDERING

1. Screen Projection:
Calculate the height of each vertical line on the screen based on the distance to the wall:
lineHeight = (int)(64 * (screenHeight / distance));

2. Fisheye Correction:
Adjust lineHeight using the cosine of the angle difference to correct for fisheye distortion:
    correctHeight = lineHeight / cos(rayAngle - playerAngle);

3. Drawing:
Draw each vertical line on the screen, adjusting for screen offset and ensuring proper vertical positioning.

note: optimize ray casting loops for performance, considering early termination when a wall is hit.
*/
