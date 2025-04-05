#include "Bridges.h"
#include "DataSource.h"
#include "Array.h"
#include "SLelement.h"
#include <sstream>


using namespace bridges;

//
//  This program illustrates how to access a small subset of the IMDB actor movie data
//  set (a list of actor movie pairs and build a linked list and visualize it.
//
int main() {

	//create the Bridges object, set credentials
	Bridges bridges(2, "Cubeacabra", "354554745725");

	bridges.setTitle("Linked List IMDB Demo");
	bridges.setDescription("Shows a linked list of movies Kevin Bacon is a part of");


	//Creates a pointer to a DataSource object on the heap, which allows Bridges to access outside data
	DataSource* ds = new DataSource;

	//Creates a vector of ActorMovieIMDB objects, where each object stores the actor, movie, genres of the movie, and movie rating
	vector<ActorMovieIMDB> data = ds->getActorMovieIMDBData2();


	//IMPORTANT NOTE: 
	// The linked list for Bridges doesn't actually use a list class. You probably can, but based on Kerney's demo code, you don't exactly need to.
	// We do still have a head, but no size or tail. Each node is linked individually as normal.


	//Create the head node, initialize to NULL
	SLelement<ActorMovieIMDB> *head = nullptr;

	//Create and Link Elements
	for (int i = 0; i < data.size(); i++) {
		ActorMovieIMDB currNode = data.at(i);
		
		//Creates the label that will display when hovering over the node in the Bridges demo
		stringstream rating;
		rating << fixed << setprecision(1) << currNode.getMovieRating();
		string label = "The Movie \"" + currNode.getMovie() + "\", Featuring \"" + currNode.getActor() + "\" Is Rated " + rating.str() + "/10 Stars";

		//Create the Node. Paramaters are for next pointer, the data stored, and the label of the node (displayed when hovered on)
		SLelement<ActorMovieIMDB>* temp = new SLelement<ActorMovieIMDB>(nullptr, currNode, label);
		
		//Link The Nodes Together
		if (i == 0) {
			temp = head;
		} else {
			temp->setNext(head);
			head = temp;
		}

	}

	//TODO: Write another for loop (formatted similar to the destructor at the bottom), that starts at the head and loops through every node, then changes their color.
	//	This can be done with the setColor method. For example, if you were wanted to change the color of head, you could write:
	//	head->setColor("green")
	//	The data we have is the actor's name, movie name, movie genres (yes, theres multiple, accessing the genre returns a vector of strings), and the movie rating.
	//	I would recomend changing the color based on the rating, but I leave that up to you. Let me know if you need any help understanding any of the code
	//	or with writing this loop!




	// tell Bridges what data structure to visualize
	bridges.setDataStructure(head);

	// visualize the list
	bridges.visualize();

	//Delete Datasource
	delete ds;

	//Delete Nodes (Essentially the destructor)
	while (head) {
		SLelement<ActorMovieIMDB>* temp = head;
		head = head->getNext();
		delete temp;
	}


	return 0;
}
