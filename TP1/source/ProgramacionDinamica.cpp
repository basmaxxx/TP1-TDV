#include "ProgramacionDinamica.h"
#include <limits>
#include <vector>


std::pair<std::vector<int>, double> encontrarSeamPDRec(const std::vector<std::vector<double>>& energia, int i, int j, int n, int m, std::vector<std::vector<std::pair<std::vector<int>, double>>>& memo) {
    if(memo[i][j].second != std::numeric_limits<double>::infinity()){   //caso base: el memo no esta vacio
        return memo[i][j];
    }
    if(i==0){                   //caso base estoy en la primera fila 
        std::pair<std::vector<int>, double > res; 
        res.first.push_back(j);
        res.second= energia[i][j];
        memo[i][j]= res;
        return res;
    }
    
    //incrementamos la energia actual



    if(j > 0 && j < m-1){    //si no estoy en un borde 
        std::pair<std::vector<int>, double > min;
        min.first= {};
        min.second= std::numeric_limits<double>::infinity();
        for(int k=j-1; k <= j+1; k++){
            std::pair<std::vector<int>, double> aux= encontrarSeamPDRec(energia, i-1, k, n , m, memo);
            if(min.second>aux.second){
                min=aux;
                }
        }
        min.first.push_back(j);
        min.second += energia[i][j];

        memo[i][j]= min;
        return memo[i][j];
    }
    else if(j==0){
        std::pair<std::vector<int>, double> min;
        min.first= {};
        min.second= std::numeric_limits<double>::infinity();
        for(int k=j; k <= j+1; k++){
            std::pair<std::vector<int>, double> aux= encontrarSeamPDRec(energia, i-1, k, n , m, memo);
            if(min.second>aux.second){
                min=aux;
                
            }
        }
        min.first.push_back(j);
        min.second += energia[i][j];
        memo[i][j]= min;
        return memo[i][j];
    }
    else{
        std::pair<std::vector<int>, double> min;
        min.first= {};
        min.second= std::numeric_limits<double>::infinity();
        for(int k=j-1; k <= j; k++){
            std::pair<std::vector<int>, double> aux = encontrarSeamPDRec(energia, i-1, k, n , m, memo);
            if(min.second>aux.second){
                min=aux;
            }
        }
        min.first.push_back(j);
        min.second += energia[i][j];
        memo[i][j]= min;
        return memo[i][j];
    }
    //PENSAR QUE HACER QUE CASO PARA PONER EL ELSE
}


std::vector<int> encontrarSeamPD(const std::vector<std::vector<double>>& energia) {
    //creo la estructura de datos-->MEMO
    int n= energia.size();
    int m= energia[0].size();
    std::vector<std::vector<std::pair<std::vector<int>, double>>> memo(
    n,
    std::vector<std::pair<std::vector<int>, double>>(
        m,
        { {}, std::numeric_limits<double>::infinity() }
    )
);


    for(int j = 0; j < m; j++){
        encontrarSeamPDRec(energia, n-1, j, n, m, memo);
    }   
    
    /*ahora busco el minimo-> luego del primer ciclo, todos los elementos de la ultima fila 
      ya estan resueltos con los minimos caminos llenos de energia*/

    //primer elemento de la ultima fila del memo(primer valor posible)
    std::pair<std::vector<int>, double> min= memo[n-1][0];

    //empiezo a comparar desde el primero
    for(int i=1; i<m; i++){
        if(min.second>memo[n-1][i].second){
            min=memo[n-1][i];
        }
    }
    return min.first;
}
