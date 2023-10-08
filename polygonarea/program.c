/*
    Problem:  https://open.kattis.com/problems/polygonarea
    CPU time: (pending)
*/

#include <stdio.h>
#include <math.h>

enum PointOrdering
{
    NONE              = 0,
    CLOCKWISE         = 1,
    COUNTER_CLOCKWISE = 2,
};

char* point_ordering_to_str(enum PointOrdering pointOrdering)
{
    switch (pointOrdering) {
        case NONE:              return "NONE";
        case CLOCKWISE:         return "CW";
        case COUNTER_CLOCKWISE: return "CCW";
        default:                return "UNKNOWN";
    }
}

struct Point
{
    int x, y;
};


struct Polygon
{
    int VerticesCount;
    struct Point* Points;
    float Area;
    enum PointOrdering Ordering;
};

void compute_polygon_area(struct Polygon* polygon)
{
    float temp = 0;

    struct Point* point_a;
    struct Point* point_b;
 
    for (int idx = 0; idx < polygon->VerticesCount; idx++) {

        point_a = (polygon->Points + idx);
        point_b = (polygon->Points + ((idx + 1 < polygon->VerticesCount) ? idx + 1 : 0));

        temp += (float)((float)point_a->x * (float)point_b->y);
        temp -= (float)((float)point_a->y * (float)point_b->x);
    }

    temp = temp / 2.0;

    polygon->Ordering = (temp > 0.0) ? COUNTER_CLOCKWISE : CLOCKWISE;
    polygon->Area     = fabs(temp);
}

int main()
{
    int verticesCount = 0;
    while (scanf("%d", &verticesCount) == 1) {
        if (verticesCount == 0) {
            return 0;
        }
        
        struct Polygon polygon;
        polygon.VerticesCount = verticesCount;

        struct Point points[polygon.VerticesCount];
        polygon.Points = points;

        for (int idx = 0; idx < polygon.VerticesCount; idx++) {
            
            struct Point* point = (polygon.Points + idx);
            int paramCount = scanf("%d%d", &point->x, &point->y);
            
            if (paramCount == 2) {
                continue;
            }

            printf("Unexpected number of parameters on line");
            return 1;
        }

        compute_polygon_area(&polygon);
        printf("%s %.1f\n", point_ordering_to_str(polygon.Ordering), polygon.Area);
    }

    return 0;
}
