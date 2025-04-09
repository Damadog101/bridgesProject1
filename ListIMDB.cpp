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
	Bridges bridges(1, "Bridges Username", "Bridges API Key");

	bridges.setTitle("Linked List IMDB Demo");
	bridges.setDescription("Shows a linked list of movies with one of their actors, and the movie's rating");


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

	// Nevan's QUESTION: Should we change something like shape of the node based on Movie Genre?

	for (SLelement<ActorMovieIMDB>* currNode = head; currNode; currNode = currNode->getNext()) { // For loop starts at head and loops through every node
		double ratingScore = currNode->getValue().getMovieRating(); // Make a placeholder for IMDB rating of the current Node
		vector<string> genre = currNode->getValue().getGenres(); // Make a placeholder for a Movie's IMDB vector of genres

		//Shape sh = WYE;
		// If statements change the color based on rating. 
		if (ratingScore <= 2.5) currNode->setColor("lime");
		else if (ratingScore > 2.5 && ratingScore <= 5) currNode->setColor("violet");
		else if (ratingScore > 5 && ratingScore <= 7.5) currNode->setColor("darkorange");
		else if (ratingScore > 7.5 && ratingScore <= 10) currNode->setColor("cyan");
		
		// Change shape based on the number of genres the Movie has
		size_t genreCount = genre.size();

		if (genreCount <= 1) currNode->setShape(Shape::WYE); // Changed "else if" since the Shapes can't run without a rating, when we want to use Genre.
		else if (genreCount <= 2) currNode->setShape(Shape::CROSS);
		else if (genreCount <= 3) currNode->setShape(Shape::SQUARE);
		else if (genreCount <= 4) currNode->setShape(Shape::TRIANGLE);
		else if (genreCount <= 5) currNode->setShape(Shape::DIAMOND);
		else if (genreCount <= 6) currNode->setShape(Shape::STAR);
		else currNode->setShape(Shape::CIRCLE);
		// Noticed that in increments of three, i.e. (genreCount <= 3) produced a majority of WYE shaped nodes.
		// Changed to current increment of one, now shape of nodes are more varied.

	}
		


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
