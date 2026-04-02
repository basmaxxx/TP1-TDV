#include "FuerzaBruta.h"

double calcular_energia(vector<int> &camino, const vector<vector<double>>& energia) {
    double total = 0;
    int n = energia.size();
    for (int i = 0; i < n; i++) {
        total += energia[i][camino[i]];
    }
    return total;
}
void encontrarSeamFuerzaBrutarrec(const std::vector<std::vector<double>>& energia, int i,int j,int n ,int m ,vector<int>&S ,vector<int>&B) {
    if(i==n){
        if(B.empty() || calcular_energia(S, energia)< calcular_energia(B,energia)){
            B=S;
        }
        return;
    }

    if(j>0){ //bajamos por la izquierda siempre y cuando no estemos en un borde
        S.push_back(j - 1);
        encontrarSeamFuerzaBrutaRec(energia, i + 1, j - 1, n, m, S, B);
        S.pop_back();
    }
    
    //en todos los casos vamos a bajar por la rama del medio
    S.push_back(j);
    encontrarSeamFuerzaBrutaRec(energia, i + 1, j, n, m, S, B);
    S.pop_back();
    
    if(j<m-1){ //bajamos por la rama derecha siempre y cuando no estemos en un borde
        S.push_back(j + 1);
        encontrarSeamFuerzaBrutaRec(energia, i + 1, j + 1, n, m, S, B);
        S.pop_back();
    }


std::vector<int> encontrarSeamFuerzaBruta(const std::vector<std::vector<double>>& energia) {
    int n= energia.size();
    int m= energia[0].size();
    vector<int> B;
    for (int j = 0; j < m; j++) { //hago la funcion recursiva por cada elemento de la primera fila
        vector<int> S;
        S.push_back(j);
        encontrarSeamFuerzaBrutaRec(energia, 1, j, n, m, S, B);
    }
    return B;
}
