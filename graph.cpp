#include <iostream>
#include <fstream>
#include <cassert>
#include <cstdlib>
#include <string>
#include <sstream>
#include <unordered_set>
#include "graph.hpp"

using namespace std;


Graph::Graph(string filename) 
  : name(filename)
  {
    ifstream indata;
    indata.open(filename);
    if (!indata) { // file couldn't be opened
      cerr << "Error: file could not be opened" << endl;
      exit(1);
    }

    indata >> size;

    this->color_mark_table = vector<Graph::t_color_mark>(size, NOT_COLOR_MARKED);
    this->shape_mark_table = vector<Graph::t_shape_mark>(size, NOT_SHAPE_MARKED);
    this->marks = vector<int>(size, -1);
    
    this->adj_lists = vector<list<pair<int,int>>>(size, list<pair<int,int>>());
    while (true) {
      int a,b;
      indata >> a;
      indata >> b;
      if (indata.eof()) break;
      this->add_edge(a,b);
    }
    indata.close();
    for (int i = 0; i < size; i++){
      this->adj_lists.at(i).sort();
    }
  }

Graph::Graph(int n)  // par défaut, le nom des fichiers est "a"
{
  this->size = n;
  this->name = "a";
  this->color_mark_table = vector<Graph::t_color_mark>(size, NOT_COLOR_MARKED);
  this->shape_mark_table = vector<Graph::t_shape_mark>(size, NOT_SHAPE_MARKED);
  this->marks = vector<int>(size, -1);
  this->adj_lists = vector<list<pair<int,int>>>(size, list<pair<int,int>>());
}
    
int Graph::get_size() const {
  return size;
}

list<int> Graph::vertices() {
  list<int> res = {};
  for (int i = size-1; i>=0; i--) 
    res.push_front(i);
  return res;
}

void Graph::add_edge(int p, int q, int weight) {
  assert(0 <= p && p < size);
  assert(0 <= q && q < size);
  pair<int,int> qq(q,weight);
  pair<int,int> pp(p,weight);
  adj_lists.at(p).push_front(qq);
  adj_lists.at(q).push_front(pp);
}

void Graph::add_edge(int p, int q) {
  this->add_edge(p,q,1);
}


bool Graph::has_edge(int p, int q) const {
  assert(0 <= p && p < size);
  assert(0 <= q && q < size);
  for (pair<int,int> i : adj_lists.at(p)) 
    if (i.first == q)
      return true;
  return false;
}

int Graph::get_weight(int p, int q) const {
  assert(0 <= p && p < size);
  assert(0 <= q && q < size);
  for (pair<int,int> i : adj_lists.at(p)) 
    if (i.first == q)
      return i.second;
  return 0;
}

list<pair<int,int>> Graph::neighbors(int p) const {
  return this->adj_lists.at(p);
}

void Graph::set_color_mark(int p, t_color_mark marked) {
  assert(0 <= p && p < size);
  color_mark_table.at(p) = marked;
}

bool Graph::is_color_marked(int p) const {
  assert(0 <= p && p < size);
  return (color_mark_table.at(p) != NOT_COLOR_MARKED);
}

Graph::t_color_mark Graph::get_color_mark(int p) const {
  assert(0 <= p && p < size);
  return (color_mark_table.at(p));
}

void Graph::set_shape_mark(int p, t_shape_mark marked) {
  assert(0 <= p && p < size);
  shape_mark_table.at(p) = marked;
}

void Graph::set_int_mark(int p,int mark){
  assert(0 <= p && p < size);
  assert(mark >= -1);
  marks.at(p) = mark;
}

int Graph::get_int_mark(int p) const{
  assert(0 <= p && p < size);
  return (marks.at(p));
}

bool Graph::is_int_marked(int p) const{
  assert(0 <= p && p < size);
  return (marks.at(p)>=0);
}

bool Graph::is_shape_marked(int p) const {
  assert(0 <= p && p < size);
  return (shape_mark_table.at(p) != NOT_SHAPE_MARKED);
}

Graph::t_shape_mark Graph::get_shape_mark(int p) const {
  assert(0 <= p && p < size);
  return (shape_mark_table.at(p));
}

bool Graph::is_marked(int p) const {
  assert(0 <= p && p < size);
  return (is_shape_marked(p) || is_color_marked(p) || is_int_marked(p));
}

void Graph::set_name(string s){
  name = s;
}

string Graph::get_name() const{
  return name;
}

void Graph::print() const {
  cout << "Size: " << size << endl;
  for (int i = 0; i < size; i++) {
    cout << i << " :";
    for (pair<int,int> j : adj_lists.at(i))
      cout << " (" << j.first << "," << j.second << ")";
    cout << endl;
  }
  cout << endl;
}

void Graph::show(bool open_eog) const {
  string dot_filename = "a.dot";
  /* nous allons générer un fichier .dot décrivant notre graphe dans la syntaxe du logiciel dot,
   * puis exécuter le logiciel dot sur ce fichier. Celui-ci produira alors un fichier image (PNG)
   * qu'on pourra ouvrir avec un logiciel de visualisation d'image.
   */

  ofstream outfile;
  outfile.open(dot_filename.c_str());
  assert(outfile.is_open());

  outfile << "graph G{" << endl; // on écrit dans le fichier.

  outfile << "node [style=filled];" << endl; // bien sûr, tout ceci est rédigé en connaissant la syntaxe du langage dot
  /* Vous pouvez ouvrir le fichier a.dot dans un éditeur de texte pour voir à quoi cela ressemble.
   * Vous pouvez aussi consulter http://en.wikipedia.org/wiki/DOT_language
   * mais ce n'est pas nécessaire pour mener le projet à bien
   */
  for (int i = 0; i < size; i++)
    outfile << i << ";" << endl;

  for (int i = 0; i < size; i++){
    string color;
    string shape;
    switch (get_color_mark(i)) {
    case YELLOW:
      color="yellow";
      break;
    case GREEN:
      color="green";
      break;
    case BLUE:
      color="blue";
      break;
    case RED:
      color="red";
      break;
    default:
      color="white";
    }
    switch (get_shape_mark(i)) {
    case SQUARE:
      shape="box";
      break;
    case TRIANGLE:
      shape="triangle";
      break;
    default:
      shape="ellipse";
    }
    
    ostringstream node_label;    
    if (is_int_marked(i)){
      node_label << "Mark = " << get_int_mark(i)<< "\\n";
    }
    node_label << i;
    outfile << i << " [fillcolor="<< color << ", shape=" << shape << ", label=\""
	    << node_label.str() << "\"];" << endl;
  }
  
  for (int i = 0; i < size; i++)
    for (pair<int,int> j : adj_lists.at(i))
      if (i<j.first) {
	if (j.second == 1){
	  outfile << i << " -- " << j.first << ";" << endl;
	}
	else {
	  outfile << i << " -- " << j.first << "[label=" << j.second << "];" << endl;
	}
      }

  outfile << "label =\"" << get_name() << "\";";
  outfile << "}" << endl;

  outfile.close(); // fin d'écriture dans le fichier a.dot

  string png_filename = "a.png";  // le nom sous lequel on veut récuperer l'image

  /* nous allons maintenant lancer le programme dot puis le programme eog
   * cela suppose que ces programmes soient présents sur votre système !
   * c'est le cas sur les machines de la salle de TP
   * pour télécharger dot, consultez http://www.graphviz.org/Download..php
   * pour remplacer eog, utilisez le visualisateur de votre système
   */

  string com1 = "dot -Tpng "+ dot_filename + " -o " + png_filename;
  system(com1.c_str());  // ceci exécute le programme dot avec les arguments idoines ; celui-ci crée alors un fichier PNG

  if (open_eog) {
    string com2 = "open " + png_filename + "&";  // le & à la fin permet de ne pas attendre la fermeture de eog pour continuer
    system(com2.c_str());  // ceci ouvre le visualisateur d'image de Gnome (inutile s'il est déjà ouvert)
  }

  cout << "Type return to proceed...";
  cout.flush();
  getchar(); // attend un appui sur entrée
}

void Graph::show() const {
  show(true); // par défaut, on ouvre eog
}

void Graph::clean_marks(){
  for(int i=0; i<get_size();i++) {
    set_color_mark(i,NOT_COLOR_MARKED);
    set_shape_mark(i,NOT_SHAPE_MARKED);
    set_int_mark(i,-1);
  }
}

void Graph::print_who_is_marked() const{
  cout << "Les sommets marqués en jaune sont :" << endl;
  for(int i=0; i<get_size();i++) {
    if (get_color_mark(i) == YELLOW){
      cout << i << " ";
    }
  }
  cout << endl;
  cout << "Les sommets marqués en vert sont :" << endl;
  for(int i=0; i<get_size();i++) {
    if (get_color_mark(i) == GREEN){
      cout << i << " ";
    }
  }
  cout << endl;
  cout << "Les sommets marqués en bleu sont :" << endl;
  for(int i=0; i<get_size();i++) {
    if (get_color_mark(i) == BLUE){
      cout << i << " ";
    }
  }
  cout << endl;
  cout << "Les sommets marqués en rouge sont :" << endl;
  for(int i=0; i<get_size();i++) {
    if (get_color_mark(i) == RED){
      cout << i << " ";
    }
  }
  cout << endl;
  cout << "Les sommets marqués avec un carré sont :" << endl;
  for(int i=0; i<get_size();i++) {
    if (get_shape_mark(i) == SQUARE){
      cout << i << " ";
    }
  }
  cout << endl;
  cout << "Les sommets marqués avec un triangle sont :" << endl;
  for(int i=0; i<get_size();i++) {
    if (get_shape_mark(i) == TRIANGLE){
      cout << i << " ";
    }
  }
  cout << endl;
}
