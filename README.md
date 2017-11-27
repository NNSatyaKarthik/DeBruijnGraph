## Addition of Dynamic Edges to Debruijn graph


You can use the editor on GitHub to maintain and preview the content for your website in Markdown files.

Whenever you commit to this repository, GitHub Pages will run Jekyll to rebuild the pages in your site, from the content in your Markdown files.

Markdown is a lightweight and easy-to-use syntax for styling your writing. It includes conventions for


De Bruijn Graphs are succinct data structures, in Bio Informatics, are used for assembly of genome sequences 
obtained from a Next Generation Sequence (NGS) library. These De Bruijn graphs must be implemented using 
data structures that are space and time efficient. Djamal Bellazzougui laid out an approach to implement 
De Bruijn graphs efficiently which supported dynamic insertion and deletion at the same time in his paper 
“Fully Dynamic De Bruijn Graphs”. The aim of our project is to implement Dynamic addition of edges into De 
Bruijn graph which is constructed using a similar compact data structures.

```markdown
# -Introduction:

De Bruijn graphs enable us to represent a sequence in terms of k-mers. The graph is basically a directed graph
with unique nodes representing k-tuples. These k-tuples are decided by starting with the first k nucleotides and
then moving forward with the next k overlapping nucleotides excluding the first nucleotide in the present tuple. 
Later, the tuples that are identical are joined and a directed graph is formed. The direction of the arrows are
such that the arrow originate from the k-mer with the last k-1 overlapping nucleotides and ending towards the k-mer
with the first k-1 overlapping nucleotides.

De Bruijn graphs are basically used to improve this memory situation by handling the assembly of reads having 
repetitive regions. This will improve the space efficiency.

There are various approaches to constructing Debruijn graph and **minimal perfect hashing** is one of them.

# -Algorithm:
The dataset which we are about to use in our algorithm is a fastq file of **E-coli K-12 MG1655 illumina sequencing 
genome** which contains a sequence genome in GBs.
The entire algorithm is designed to work in the given steps:

- **Construction of Debruijn Graph:**
  -  Each read is passed sequentially into the the DBGraph Construction which constructs a De Bruijn graph dynamically 
     adding new vertices and edges into the graph DB.
  -  For each sequence of size N split the sequence into array of size (n − k) each element with length k. Initialize 
     the Graph DB with matrix of size N * σ (σ being the size of the distinct alphabets of sequence)
  -  For each sequence reads, construct k-mers of the reads. Add consecutive k-mer1 and k-mer2 vertices if not present. 
     Then add an edge between those vertices using AddDynamicEdge algorithm.
     
- **Adding Dynamice Edges:**
  -  Given a Debruijn Graph DB and 2 K-mers, we compute the hash of U and V for finding the indices of the IN and OUT
     matrices. 
  -  Initialize all the constants desiredsz, minht, maxht,midht. IN and OUT matrices are set to 1 for adding an edge
     between 2 K-mers.    
  -  Check if both the K-mers are in different components in the G in O(k log2 σ) time using Depth First Traversal:
     - If the SzU and SzV components are both < desiredsz then Merge both the components. 
     - If only one of the U or V component’s size is lesser than desiredsz then we check for height of the bigger 
       component. 
     - If the height of the bigger component is greater than the midht, then we need to break the bigger component 
       into two components as its height might cross maxht.
     - If the height of the bigger Component is < midht then we might need to just Merge with no break needed in the 
       bigger component as addition of new component of height < desiredsz doesn’t affect any violation to our conditions.
  -  We repeat this process till all the Edges are added into the G.

- **Merge two connected components:**
  -  Given a graph G and 2 K-mers Ui and Vi (Indices of the K-mers), there is a need to merge U to V . This merge
     function’s 2nd and the 3rd parameters are always the smaller components . Within the Merge method, it changes the 
     direction of all the parent pointers in U’s component to point to the vertex U. This takes the time O(k log2 σ). 
  -  Once all the parent pointers are changed to U, mark U as the new root of U’s Component.
  -  Now, the bigger component might be needed to break into two parts in order to satisfy the height conditions. If the
     size of the bigger component is > midht, then the condition(< maxht) on height may be violated when we merge the 
     smaller component into the bigger one. 
  -  We traverse the desiredsz height in bigger component and break all the parent points at the level of height
     desiredsz-1.We choose one of the boundary as the new root of the U component. We sample the nodes in the broken 
     component and change the directions of parent pointers for finding the new root of the broken component.

- **Performance evaluations:**
  We are using a small portion of code that would be dedicated to time and memory consumption of the entire project. To 
  check for the time utilized in this algortihm, we set a timer from the sequence read till the end of the merging components.
  
  However, to check for memory performance, we are checking out the process id or process name for our current code and 
  passing it as argument to the handle for Operating System in the code which gives the memory performance in bits. 
  Note: With different operating systems, there are different libraries to run code for memory performance.ex:- POSIX 
  library in case of Linux and windows.h library in Windows. 
  
  There are few third-party tools existing to monitor code performance like Valgrind.
  
# Steps to run the code:

- Our algorithms have been written in C++. We have used **CLion editor** to write and run the code. 
- It is really important to have a FASTQ file for above stated sequence which you get from 
  [European Nucleotide Archive](https://www.ebi.ac.uk/ena/data/view/ERX008638)
- Once the GB data is taken, 

- Bulleted
- List

1. Numbered
2. List

**Bold** and _Italic_ and `Code` text

[Link](url) and ![Image](src)
```

For more details see [GitHub Flavored Markdown](https://guides.github.com/features/mastering-markdown/).

### Jekyll Themes

Your Pages site will use the layout and styles from the Jekyll theme you have selected in your [repository settings](https://github.com/NNSatyaKarthik/DeBruijnGraph/settings). The name of this theme is saved in the Jekyll `_config.yml` configuration file.

### Support or Contact

Having trouble with Pages? Check out our [documentation](https://help.github.com/categories/github-pages-basics/) or [contact support](https://github.com/contact) and we’ll help you sort it out.
