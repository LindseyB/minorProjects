/****************************************************
 *  vector.c - a simple vector (dynamic array) of 
 *  data structs
 *                                                  
 *  Lindsey Bieda
 ****************************************************/


#include <stdlib.h>
#include <string.h>

// name identifies the data and bytes stores the data itself
struct data
{
	char *name;
	long bytes;
};

struct data** vector;

int size, len;
int flagalloc = 0;

void vector_new(); // init the vector
void vector_add(struct data*); // adds data to the vector
long vector_remove(char*); // removes data given a name and returns the value
void vector_resize(); // resize the vector
long vector_get(char*); // get bytes for given name
void vector_clear(); // clear the vector
void vector_free(); // deallocate vector


void vector_new()
{
	//inital size is 10
	size = 10;
	len = 0;
	vector = malloc(size * sizeof(struct data*));
}

void vector_add(struct data* datum)
{
	int i;

	// if no vector is initalized allocate memory for it
	if(flagalloc == 0)
	{
		vector_new();
		flagalloc = 1;
	}

	// if data by the name already exists
	if(vector_get(datum->name) != -1)
	{
		for(i = 0; i<len; i++)
		{
			// replace the data 
			if(strcmp(vector[i]->name, datum->name) == 0)
			{
				vector[i]->bytes = datum->bytes;
				return;
			}
		}
	}

	if(len < size)
	{
		//add to vector
		vector[len] = datum;
	}
	else
	{
		//resize
		vector_resize();
		
		//add to vector
		vector[len] = datum;
	}

	len++;
}

long vector_remove(char* name)
{
	int i,j;
	long temp;

	if(vector_get(name)==-1)
		return -1;

	for(i = 0; i<len; i++)
	{
		if(strcmp(vector[i]->name, name) == 0)
		{
			//remove it
			temp = vector[i]->bytes;
			free(vector[i]);
			for(j=i; j<len-1; j++)
			{
				vector[j] = vector[j+1];
			}
		}

		break;
	}

	return temp;


}

void vector_resize()
{
	int temp = len;
	int i;
	struct data** vector_new;
	size = size * 2; 
	
	// create a new vector of size
	vector_new = malloc(size * sizeof(struct data*));
	
	// copy elements and free old vector
	for(i=0; i<len; i++)
	{
		vector_new[i] = malloc(sizeof(struct data*));
		vector_new[i]->name = vector[i]->name;
		vector_new[i]->bytes = vector[i]->bytes;
	}

	vector_free();
	vector = vector_new;

	len = temp;
}

long vector_get(char* name)
{
	int i;
	for(i = 0; i<len; i++)
	{
		// if the string matches the name return the data
		if(strcmp(vector[i]->name, name) == 0)
			return vector[i]->bytes;
	}

	// if not found return -1
	return -1;
}

void vector_clear()
{
	int i;
	
	for(i=0; i<len; i++)
	{
		free(vector[i]);
	}

	len = 0;

}

void vector_free()
{
	vector_clear();
	free(vector);
}

void main(){}