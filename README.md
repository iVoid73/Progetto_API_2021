# API project 2021
This is the repository of the **Algoritmi e Principi dell'informatica** course held at **Politecnico di Milano**

Teacher **Alessandro Barenghi**  
A.Y. **2020/2021**

Final grade **30/30 cum Laude**

## Specification

You can find the full pdf specification (in Italian) [here](https://github.com/iVoid73/Progetto_API_2021/blob/main/Specifica%20del%20Progetto.pdf).

The goal of the project is to handle a ranking among direct weighted graphs.
- The ranking keeps the *best* k graphs

The program to be
realized has in input
- Two parameters once (on the first row of the file, with a space in between):
	- **d**: the number of nodes of each graph
	- **k**: the lenght of the ranking
- A squence of commands that could be either:
	- **AggiungiGrafo** [Adjacence matrix]
	The adjacence matrix is a *d x d* matrix and in each position *(i, j)* has an integer representing the weight of the arc between node *i* and node *j* - If there's a 0, it means that there is no arc
	- **TopK**

The program must print the k-long ranking (the order is not relevant) each time it reads a TopK command.
The criterion to rank the graphs is the **sum of the weights of the minimum paths from node 0 to each other node** (the lower the sum, the better it is).


## Example
3,2  
AggiungiGrafo  
0,4,3  
0,2,0  
2,0,0  
AggiungiGrafo   
0,0,2  
7,0,4  
0,1,0  
AggiungiGrafo  
3,1,8  
0,0,5  
0,9,0  
TopK  

**Expected Output**
1 0 (or 0 1)
