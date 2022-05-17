#include "Node.hpp"

namespace ariel
{
    class OrgChart
    {
    private:
        Node root;
    public:
        OrgChart(/* args */);
        ~OrgChart();
        void add_root(string name){}
        void add_sub(string name, string father){}
    };
    
    OrgChart::OrgChart(/* args */)
    {
    }
    
    OrgChart::~OrgChart()
    {
    }
    
} // namespace ariel
