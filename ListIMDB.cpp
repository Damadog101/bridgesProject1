#include "Bridges.h"
#include "DataSource.h"
#include "Array.h"
#include "SLelement.h"


using namespace bridges;

//
//  This program illustrates how to access a small subset of the IMDB actor movie data
//  set (a list of actor movie pairs and build a linked list and visualize it.
//
int main() {

  //create the Bridges object, set credentials
  Bridges bridges(101, "BRIDGES_USER_ID", "BRIDGES_API_KEY");

  bridges.setTitle("List IMDB");
  bridges.setDescription("Shows a linked list of movies Kevin Bacon is a part of");

  // TODO:  access teh IMDB dataset - create a  data source object 
  // and use its getActorMovieIMDBData() method
  // this will return a list (vector) of actor-movie objects of type
  // ActorMovieIMDB - refer to the docs for that object and its attributes

  // TODO: build a linked list, using singly linked list elements, SLElement<ActorMovieIMDB>
  // where the actormovie object is a generic parameter that

  // iterate through the vector and put each of the actor movie names into the label
  // field of the SLelement (using the setLabel() method of the element) -
  // this will show up in the visualization when you do a moouse over the node
  // mark the first node of the list by changing its color (use the setColor()
  // method)

  SLelement<ActorMovieIMDB> *head = nullptr;


  // tell Bridges what data structure to visualize
  bridges.setDataStructure(head);

  // visualize the list
  bridges.visualize();

  //free the list as you have created dynamic memory

  return 0;
}
