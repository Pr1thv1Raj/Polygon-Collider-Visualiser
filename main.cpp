#include <bits/stdc++.h>

using namespace std;

double d[2];

double normalize(double x1,double y1, bool xYes){
    double denom = sqrt(x1*x1 + y1*y1);
    if( xYes) {
        return  x1/denom ;
    }
    else{
        return y1/denom ;
    }

}

double dot(double x1, double y1 , double x2, double y2){
return x1*x2 + y1*y2 ;
}

double tripleProduct(double A[2],double B[2], double C[2], bool xYes){
 if(xYes){
    return (A[0]*C[0] + A[1]*C[1])*B[0] - (A[0]*B[0] + A[1]*B[1])*C[0];
 }
 else{
     return (A[0]*C[0] + A[1]*C[1])*B[1] - (A[0]*B[0] + A[1]*B[1])*C[1];
 }


}

int farthestPointIndex(vector<pair<double,double>> s, double dir[2]){
  double dotproduct = s[0].first*dir[0] + s[0].second*dir[1];
  int ans = 0;
  for( int i = 0 ; i < 3 ; i++){
    if(s[i].first*dir[0] + s[i].second*dir[1] > dotproduct){ dotproduct = s[i].first*dir[0] + s[i].second*dir[1]; ans = i; }
  }
  return ans;
}

double support(vector<pair<double,double>> a1, vector<pair<double,double>> a2, double dir[2], bool xYes ){
    if( xYes){
            double negD[2];
      negD[0] = -dir[0];
      negD[1] = -dir[1];
        return a1[farthestPointIndex(a1,dir)].first - a2[farthestPointIndex(a2,negD)].first;
    }
    else{
            double negD[2];
      negD[0] = -dir[0];
      negD[1] = -dir[1];
        return a1[farthestPointIndex(a1,dir)].second - a2[farthestPointIndex(a2,negD)].second;
    }
}

double centroid(vector <pair<double,double>> tri, bool xYes){
    if(xYes){ return (tri[0].first + tri[1].first + tri[2].first)/3 ;}
    else {
        return (tri[0].second + tri[1].second + tri[2].second)/3 ;
    }

}
bool lineCase(vector<pair<double,double>> simplex, double dir[2]){
    double AB[2],AO[2];
    AB[0] = simplex[0].first - simplex[1].first;
    AB[1] = simplex[1].second - simplex[1].second;
    AO[0] = -simplex[1].first;
    AO[1] = -simplex[1].second;
    double ABperp[2];
    ABperp[0] = tripleProduct(AB,AO,AB,true);
    ABperp[1] = tripleProduct(AB,AO,AB,false);
    d[0] = normalize(ABperp[0],ABperp[1],true);
    d[1] = normalize(ABperp[0],ABperp[1],false);
    return false;

}
bool triangleCase(vector<pair<double,double>> simplex, double dir[2]){
    double AB[2],AC[2],AO[2];
    AB[0] = simplex[1].first - simplex[2].first;
    AB[1] = simplex[1].second - simplex[2].second;
    AC[0] = simplex[0].first - simplex[2].first;
    AC[1] = simplex[0].second - simplex[2].second;
    AO[0] = -simplex[2].first;
    AO[1] = -simplex[2].second;
    double ABperp[2],ACperp[2];
    ABperp[0] = tripleProduct(AC,AB,AB,true);
    ABperp[1] = tripleProduct(AC,AB,AB,false);
    ACperp[0] = tripleProduct(AB,AC,AC,true);
    ACperp[1] = tripleProduct(AB,AC,AC,false);
    if( dot(ABperp[0],ABperp[1],AO[0],AO[1]) > 0){
        simplex.erase(simplex.begin());
        d[0] = normalize(ABperp[0],ABperp[1],true);
        d[1] = normalize(ABperp[0],ABperp[1],false);
        return false;
    }
    else if ( dot(ACperp[0],ACperp[1],AO[0],AO[1]) > 0){
        simplex.erase(simplex.begin() +1 );
        d[0] = normalize(ACperp[0],ACperp[1],true);
        d[1] = normalize(ACperp[0],ACperp[1],false);
        return false;
    }
   return true;
}

bool handleSimplex(vector<pair<double,double>> simplex, double d[2]){
 if( simplex.size() == 2){ return lineCase(simplex,d);}
 return triangleCase(simplex,d);
}

bool gjk( vector<pair<double,double>> s1, vector<pair<double,double>> s2 ){

    double c1[2];
    double c2[2];
    c1[0] = centroid(s1,true);
    c1[1] = centroid(s1,false);
    c2[0] = centroid(s2,true);
    c2[1] = centroid(s2,false);
//    cout << c1[0] << " " << c1[1] << endl;
//    cout << c2[0] << " " << c2[1] << endl;
    d[0] = normalize(c2[0]-c1[0],c2[1]-c1[1],true);
    d[1] = normalize(c2[0]-c1[0],c2[1]-c1[1],false);
//    cout << d[0] << " " << d[1] ;
    vector<pair<double,double>> simplex;
    simplex.push_back(make_pair(support(s1,s2,d,true),support(s1,s2,d,false)));
//    cout << simplex[0].first << " " << simplex[0].second << endl;
     d[0] = -d[0];
     d[1] = -d[1];
     while(true){
        double a[2];
        a[0] = support(s1,s2,d,true);
        a[1] = support(s1,s2,d,false);

        if(dot(d[0],d[1],a[0],a[1]) < 0){
            return false;
        }
        simplex.push_back(make_pair(a[0],a[1]));
      if(handleSimplex(simplex,d)){
        return true;
      }
    }


}


int main()
{
vector<pair <double,double>> s1;
vector<pair <double,double>> s2;
  for(int i = 0 ; i < 3 ; i++){
    double a,b;
    cin >> a >> b;
    s1.push_back(make_pair(a,b));
  }
  for(int i = 0 ; i < 3 ; i++){
    double a,b;
    cin >> a >> b;
    s2.push_back(make_pair(a,b));
  }
  gjk(s1,s2);

}
