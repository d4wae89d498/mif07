#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <list>
#include <unordered_set>

using namespace std;


class Graph {
/*
 * déclaration de types
 */
public:
  enum t_color_mark {NOT_COLOR_MARKED, YELLOW, GREEN, BLUE, RED}; // idem pour noter l'existence d'un arc
  enum t_shape_mark {NOT_SHAPE_MARKED, SQUARE, TRIANGLE};

/*
 * déclaration de champs et méthodes
 */
private:
  int size;
  string name;
  vector<list<pair<int,int>>> adj_lists; // vecteur de vecteurs, donc matrice
  vector<t_color_mark> color_mark_table; // vecteur unidimensionnel
  vector<t_shape_mark> shape_mark_table;
  vector<int> marks;
  
public:
  Graph(string filename);
  Graph(int n);
  int get_size() const; // rend le nombre de sommets
  bool has_edge(int p, int q) const; // indique si pq est une arête
  int get_weight(int p, int q) const; // renvoie le poids de l'arête pq
  void add_edge(int p, int q, int weight);
  void add_edge(int p, int q); // par défaut, le poids est 1
  list<pair<int,int>> neighbors(int p) const;
  list<int> vertices();

  // fonctions de marquage de sommets 
  void set_color_mark(int p, t_color_mark marked); // place (ou retire) une marque de couleur sur le sommet p
  bool is_color_marked(int p) const; // indique si le sommet p est marqué d'une couleur
  t_color_mark get_color_mark(int p) const;
  void set_int_mark(int p, int mark);
  int get_int_mark(int p) const;
  bool is_int_marked(int p) const;
  void set_shape_mark(int p, t_shape_mark marked); // place (ou retire) une marque sur le sommet p
  bool is_shape_marked(int p) const; // indique si le sommet p est marqué d'une forme
  t_shape_mark get_shape_mark(int p) const;
  bool is_marked(int p) const;
  void clean_marks();

  // donner un nom au graphe
  void set_name(string s);
  string get_name() const;
  
  // affichage et debug
  void print() const;  // affichage en mode texte dans la console
  void show(bool open_eog) const; // affichage graphique ; open_eog permet d'indiquer qu'il faut lancer le visualisateur d'image "eye of gnome". S'il est déjà ouvert, il n'est pas utile de le rouvrir (l'affichage se met à jour automatiquement), et ne pas le rouvrir permet de garder le focus sur la console
  void show() const; // par défaut, on ouvre eog
  void print_who_is_marked() const;
};





