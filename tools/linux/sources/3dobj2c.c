#include <string.h> /* a header needed for scanf function */
#include <stdio.h>  /* a header needed for FILE */

/* define the pointer for the input file globally */
FILE *infile;
FILE *outfile;

void print_help()
{
  printf("USAGE:\n\n");
  printf("3dconv <inputfile>.obj <outputfile>.h\n");
}

void print_hello()
{
  printf("--------------------------------------------------\n");
  printf("Simple 3d OBJ file to C source converter\n");
  printf("by Emanuel Schleussinger 2002. http://www.ngine.de\n");
  printf("--------------------------------------------------\n\n");
}


int main(int argc, char** argv)
{
     char word[50]; /* no word above 50 characters */
     char objnumber[5]; /* not more than 99999 objects */
     char strnumverts[5]; /* not more than 99999 objects */
     char strnumfaces[5]; /* not more than 99999 objects */
     int tmpint;
     char obj_reached=0;
     char vertex_reached=0;
     int  num_verts=0;
     char faces_reached=0;
     int  num_faces=0;
     char current_tag;

     print_hello();

  if(argc!=3)
  {
    print_help();
    return(1);
  }


/* open input file n.b. no test for the case that filled does
   not exist */
     infile  = fopen(argv[1], "r");
     outfile = fopen(argv[2], "w");
     
     if(infile==NULL)
     {
       printf("File does not exist. Exiting \n");
       return(2);
     }

     fprintf(outfile,"// object info created by schleuss 3dconv\n");
     fprintf(outfile,"\n");

     while( fscanf( infile, " %s", word)!=EOF)
         {
	   //Get Title of OBJ
	   if(strcmp("Object:",word)==0)
	     {
	       fscanf( infile, " %s", word);
	       strcpy(objnumber,word);
	       fprintf(outfile,"\n\n// Object number: %s\n",objnumber);
	     }
	   //Get number of faces
	   if(strcmp("Vertices:",word)==0)
	     {
	       fscanf( infile, " %s", word);
	       strcpy(strnumverts,word);
	     }
	   //Get number of faces
	   if(strcmp("Faces:",word)==0)
	     {
	       fscanf( infile, " %s", word);
	       strcpy(strnumfaces,word);
	     }
	   //Get Vertex data
	   if(strcmp("v",word)==0)
	     {
	       if(!vertex_reached)
		 {
		   fprintf(outfile,"float vertlist%s[]={\n ",objnumber);
		   vertex_reached=1;
		   current_tag='v';
		 }
	       else
		 {
		   fprintf(outfile,",");
		 }
	       fscanf( infile, " %s", word);
	       fprintf(outfile,"%12s,",word);
	       fscanf( infile, " %s", word);
	       fprintf(outfile,"%12s,",word);
	       fscanf( infile, " %s", word);
	       fprintf(outfile,"%12s,",word);
	       fprintf(outfile,"   1 \n");
	       num_verts++;
	     }
	   //Get Poly data
	   if(strcmp("f",word)==0)
	     {
	       if(current_tag=='v')
		 {
		   //close vertices src table
		   fprintf(outfile,"\n};\n\n\n");
		   current_tag='f';
		 }

	       if(!faces_reached)
		 {
		   fprintf(outfile,"u32 polylist%s[]={\n ",objnumber);
		   faces_reached=1;
		 }
	       else
		 {
		   fprintf(outfile,",");
		 }
	       fscanf( infile, " %s", word);
	       tmpint=atoi(word);
	       fprintf(outfile,"%5d,",tmpint-1);
	       fscanf( infile, " %s", word);
	       tmpint=atoi(word);
	       fprintf(outfile,"%5d,",tmpint-1);
	       fscanf( infile, " %s", word);
	       tmpint=atoi(word);
	       fprintf(outfile,"%5d,",tmpint-1);
	       fscanf( infile, " %s", word);
	       tmpint=atoi(word);
	       fprintf(outfile,"%5d \n",tmpint-1);
	       num_faces++;
	     }
	   
         } /* end of while construction */

	   fprintf(outfile,"};\n\n");
	   fprintf(outfile,"u32 num_vert%s=%d;\n",objnumber,num_verts);
	   fprintf(outfile,"u32 num_face%s=%d;\n",objnumber,num_faces);

	   
	   return(0);
	   

} /* end of main function */


