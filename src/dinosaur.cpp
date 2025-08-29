#include <utils.hpp>

bool isCollided(const rect& a, const rect& b) {
    return (a.right() < b.left() && a.left() > b.right() && 
            a.bot() < b.top() && a.top() > b.bot());
}