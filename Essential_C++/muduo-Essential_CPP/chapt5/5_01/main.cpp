#include "LibMat.hpp"

void print(LibMat object,const LibMat *pointer,const LibMat &reference)
{
    cout << "In global print(): about to print mat.print()" << endl;
    object.print();
    cout<<"*********"<<endl;
    pointer->print();
    cout<<"*********"<<endl;
    reference.print();
    cout<<"*********"<<endl;
}

int main()
{
    // cout << "\nCreating a LibMat object to print()" << endl;
    // LibMat libmat;
    // print(libmat);

    // cout << "\nCreating a Book object to print()" << endl;
    // Book b("The Castle", "Franz Kafka");
    // print(b);
    //cout<<endl;
    //cout << "\nCreating a AudiBook object to print()" << endl;
    //AudioBook ab("Man Without Qualities", "Robert Musil", "Keneth Meyer");
    //cout << "\nthe author of the book is" << endl;
    //<<ab.author()<<endl;
    // print(ab);
    cout<<endl;

    cout<<"**test put an child object to parent"<<endl;
    //LibMat * audio = new AudioBook("Man Without Qualities", "Robert Musil", "Keneth Meyer");
    //print(*audio);
    //delete audio;
    AudioBook iwash("Man Without Qualities", "Robert Musil", "Keneth Meyer");
    print(iwash,&iwash,iwash);
    cout<<endl;
    
    
    return 0;
}