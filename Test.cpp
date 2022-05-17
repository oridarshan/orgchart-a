/**
 *
 * AUTHORS: Ori Darshan
 *
 * Date: 2022-05
 */

#include "doctest.h"
#include "sources/OrgChart.hpp"
using namespace ariel;

#include <string>
#include <algorithm>
using namespace std;

TEST_CASE("general organization functions"){
    OrgChart organization;
    // add_root
    CHECK_NOTHROW(organization.add_root("Father"););
    // add_sub
    CHECK_NOTHROW(organization.add_sub("Father", "Child"););
    // change root
    CHECK_NOTHROW(organization.add_root("Step-father"););
}

/* Complex chart for testing:
                     Father
                        |
             |----------------------------|
           Child1                          Child2
             |
    |------------------|
Grandchild1       Grandchild2     
*/

TEST_CASE("level_order_iterator"){
    OrgChart organization;
    organization.add_root("Father")
      .add_sub("Father", "Child1")
      .add_sub("Father", "Child2")
      .add_sub("Child1", "Grandchild1")
      .add_sub("Child1", "Grandchild2");
    // level_order iterator starts and stops as intended
    // ++ operator, != operator
    auto it = organization.begin_level_order();
    auto end = organization.end_level_order();
    // different start-end
    CHECK(it != end);
    // loop over chart
    CHECK(*it == "Father");
    // procced through chart
    CHECK_NOTHROW(++it;);
    CHECK(it != end);
    CHECK((*it == "Child1" || *it == "Child2"));
    ++it;
    CHECK(it != end);
    CHECK((*it == "Child2" || *it == "Child1"));
    ++it;
    CHECK(it != end);
    CHECK((*it == "Grandchild1" || *it == "Grandchild2"));
    ++it;
    CHECK(it != end);
    CHECK((*it == "Grandchild2" || *it == "Grandchild1"));
    ++it;
    CHECK_FALSE(it != end);
}

TEST_CASE("reverse_order_iterator"){
    OrgChart organization;
    organization.add_root("Father")
      .add_sub("Father", "Child1")
      .add_sub("Father", "Child2")
      .add_sub("Child1", "Grandchild1")
      .add_sub("Child1", "Grandchild2");

    // reverse_order iterator starts and stops as intended
    // ++ operator, != operator
    auto it = organization.begin_reverse_order();
    auto end = organization.end_reverse_order();
    
    // procced through chart
    CHECK(it != end);
    CHECK((*it == "Grandchild1" || *it == "Grandchild2"));
    CHECK_NOTHROW(++it;);
    CHECK(it != end);
    CHECK((*it == "Grandchild2" || *it == "Grandchild1"));
    ++it;
    CHECK(it != end);
    CHECK((*it == "Child1" || *it == "Child2"));
    ++it;
    CHECK(it != end);
    CHECK((*it == "Child2" || *it == "Child1"));
    ++it;
    CHECK(*it == "Father");
    ++it;
    CHECK_FALSE(it != end);

}
TEST_CASE("preorder_iterator"){
    OrgChart organization;
    organization.add_root("Father")
      .add_sub("Father", "Child1")
      .add_sub("Father", "Child2")
      .add_sub("Child1", "Grandchild1")
      .add_sub("Child1", "Grandchild2");
    // preorder iterator starts and stops as intended
    // ++ operator, != operator
    auto it = organization.begin_preorder();
    auto end = organization.end_preorder();
    // different start-end
    CHECK(it != end);
    // loop over chart
    CHECK(*it == "Father");
    // procced through chart
    CHECK_NOTHROW(++it;);
    CHECK(it != end);
    CHECK((*it == "Child1" || *it == "Child2"));
    // Child1 came first
    if (*it == "Child1")
    {
        ++it;
        CHECK(it != end);
        CHECK((*it == "Grandchild1" || *it == "Grandchild2"));
        ++it;
        CHECK(it != end);
        CHECK((*it == "Grandchild2" || *it == "Grandchild1"));
        ++it;
        CHECK(it != end);
        CHECK(*it == "Child1");
        ++it;
    }
    // Child2 came first
    else
    {
        ++it;
        CHECK(it != end);
        CHECK(*it == "Child1");
        ++it;
        CHECK(it != end);
        CHECK((*it == "Grandchild1" || *it == "Grandchild2"));
        ++it;
        CHECK(it != end);
        CHECK((*it == "Grandchild2" || *it == "Grandchild1"));
        ++it;
    }
    CHECK_FALSE(it != end);
}

TEST_CASE("general iterator (level-order like)"){
    OrgChart organization;
    organization.add_root("Father")
      .add_sub("Father", "Child1")
      .add_sub("Father", "Child2")
      .add_sub("Child1", "Grandchild1")
      .add_sub("Child1", "Grandchild2");
    // general iterator starts and stops as intended
    // ++ operator, != operator
    auto it = organization.begin();
    auto end = organization.end();
    // different start-end
    CHECK(it != end);
    // loop over chart
    CHECK(*it == "Father");
    // procced through chart
    CHECK_NOTHROW(++it;);
    CHECK(it != end);
    CHECK((*it == "Child1" || *it == "Child2"));
    ++it;
    CHECK(it != end);
    CHECK((*it == "Child2" || *it == "Child1"));
    ++it;
    CHECK(it != end);
    CHECK((*it == "Grandchild1" || *it == "Grandchild2"));
    ++it;
    CHECK(it != end);
    CHECK((*it == "Grandchild2" || *it == "Grandchild1"));
    ++it;
    CHECK_FALSE(it != end);
}