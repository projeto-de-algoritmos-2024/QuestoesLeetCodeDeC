#include <ios>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <climits>

using namespace std;

class Point {

public:
  int x, y;
    
  Point(int x, int y){
      this->x = x;
      this->y = y;
  }
};

class ClosestTriplet {
public:

    vector<Point> points;

    ClosestTriplet(vector<Point> points) {
        this->points = points;
    }

    double calc_distance(Point point_1, Point point_2) {
        return sqrt(pow(point_1.x - point_2.x, 2) + pow(point_1.y - point_2.y, 2));
    }

    double calc_triplet_distance(Point point_1, Point point_2, Point point_3) {
        return calc_distance(point_1, point_2) + calc_distance(point_1, point_3) + calc_distance(point_2, point_3);
    }

    double closest_distance() {
        sort(points.begin(), points.end(), [](Point point_1, Point point_2) { 
          return point_1.x < point_2.x; 
        });

        pair<double, vector<Point>> closest_distance = closest_triplet(points);
        return closest_distance.first;
    }

private:

    pair<double, vector<Point>> closest_triplet(vector<Point> &points) {

        int num_points = points.size();
        if (num_points < 3) {
            return {INFINITY, {}};
        }

        int median = num_points / 2;
        vector<Point> left(points.begin(), points.begin() + median);
        vector<Point> right(points.begin() + median, points.end());

        auto left_closests = closest_triplet(left);
        auto right_closests = closest_triplet(right);

        double smallest_distance = min(left_closests.first, right_closests.first);
        vector<Point> closest_triplet_points = left_closests.first < right_closests.first ? left_closests.second : right_closests.second;

        int median_x = points[median].x;
        vector<Point> candicates;
        
        for (auto& point : points) {
            if (abs(point.x - median_x) < smallest_distance) {
                candicates.push_back(point);
            }
        }

        sort(candicates.begin(), candicates.end(), [](Point point_1, Point point_2) { 
            return point_1.y < point_2.y; 
        });

        for (int i = 0; i < candicates.size(); i++) {
            for (int j = i + 1; j < min(i + 15, (int)candicates.size()); j++) {
                for (int k = j + 1; k < min(j + 15, (int)candicates.size()); k++) {
                    double distance = calc_triplet_distance(candicates[i], candicates[j], candicates[k]);
                    if (distance < smallest_distance) {
                        smallest_distance = distance;
                        closest_triplet_points = {candicates[i], candicates[j], candicates[k]};
                    }
                }
            }
        }

        return {smallest_distance, closest_triplet_points};
    }
};

int main(void) {
    int N;
    while (cin >> N) {
        if (N == -1) {
            break;
        }

        vector<Point> points;
        for (int i = 0; i < N; i++) {
            int x, y;
            cin >> x >> y;
            points.push_back(Point(x, y));
        }

        ClosestTriplet closest_triplet(points);
        auto result = closest_triplet.closest_distance();
        cout << fixed;
        cout.precision(3);
        cout << result << endl;
    }
    return 0;
}

