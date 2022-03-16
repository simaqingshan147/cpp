#include"textQuery.h"
#include"query.h"
using namespace std;

int main(){
    ifstream out("input.txt",fstream::in);
    TextQuery tq(out);
    auto res = Query("you")&Query("have");
    cout<<res<<endl;
    print(cout,res.eval(tq));
    return 0;
}