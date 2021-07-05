/*
    Name: Abdulkadir
    Surname: Pazar
    Compile command: g++ 150180028.cpp -o 150180028
*/

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <cstdlib>

using namespace std;

class Neuron{
    protected:
    double value;
    double activated_value;

    public:
    Neuron(){
        value = 0; 
        activated_value = 0;
    }
    virtual void activate() = 0;
    double getValue(){return value;}
    double getActivatedValue(){return activated_value;}
    void setValue(double value_in){value = value_in;}
    void setActivatedValue(double activated_value_in){activated_value = activated_value_in;}

};

class SigmoidNeuron : public Neuron{
    public:
    void activate(){
        activated_value =  1 / (1 + exp(-1 * value));
    }
};

class ReluNeuron : public Neuron{
    public:
    void activate(){
        activated_value = (0.0 < value) ? value: 0.0;
    }
};

class LReluNeuron : public Neuron{
    public:
    void activate(){
        activated_value = (0.1 * value < value) ? value: 0.1 * value;
    }
};

class Layer{
    Neuron* neuronarr;

    public:
    Layer(){}
    Layer(int count, int type){
        if(type == 0)
            neuronarr = new SigmoidNeuron[count];
        if(type == 1)
            neuronarr = new LReluNeuron[count];
        if(type == 2)
            neuronarr = new ReluNeuron[count];
    }
    Neuron* getNeuronarr(){return neuronarr;}
    ~Layer(){delete [] neuronarr;}
};

class Network{
    Layer* layerarr;
    int layercount;

    public:
    Network(int size, int* neuroncount, int* neurontype){
        layercount = size;
        layerarr = new Layer[size];
        for(int i = 0; i < size; i++){
            Layer* ptr = new Layer(neuroncount[i], neurontype[i]);
            layerarr[i] = *ptr;
        }
    }
    Layer* getLayerarr(){return layerarr;}
    ~Network(){delete [] layerarr;}
};

void checkErrors(int* typearr, int size, int input)
{
    if(input != '\000') throw "Input shape does not match!"; 
    for(int i = 0; i < size; i++){
        if(typearr[i] < 0 || typearr[i] > 2) throw "Unidentified activation function!";
    }
}

int main(int argc, char** argv)
{
    ifstream in;
    int layercount;
    int* neuroncounts;
    int* neurontypes;
    int* inputs;
    char input = '\000';
    in.open(argv[1]);
    in >> layercount;
    neuroncounts = new int[layercount];
    neurontypes = new int[layercount];
    inputs = new int[layercount];
    for(int i = 0; i < layercount; i++){
        in >> neuroncounts[i];
    }
    for(int i = 0; i < layercount; i++){
        in >> neurontypes[i];
    }
    for(int i = 0; i < layercount; i++){
        in >> inputs[i];
    }
    in >> input;
    in.close();

    try{
        checkErrors(neurontypes, layercount, input);
    }
    catch(const char* error){
        cout << error << endl;
        return EXIT_FAILURE;
    }
    Network network(layercount, neuroncounts, neurontypes);
    
    //fill Layer 0
    for(int i = 0; i < neuroncounts[0]; i++){
        network.getLayerarr()[0].getNeuronarr()[i].setValue(inputs[i]);
        network.getLayerarr()[0].getNeuronarr()[i].setActivatedValue(inputs[i]);
    }

    for(int i = 1; i < layercount; i++){
        int w_size = neuroncounts[i] * neuroncounts[i - 1];
        int b_size = neuroncounts[i];
        int z_size = neuroncounts[i];
        int a_size = neuroncounts[i - 1];
        double* w = new double[w_size];
        double* b = new double[b_size];
        double* z = new double[z_size];
        double* a = new double[a_size];
        //fill w matrix
        for (int w_index = 0; w_index < w_size; w_index++){    
            w[w_index] = 0.1;
        }
        //fill b vector
        for(int b_index = 0; b_index < b_size; b_index++)
            b[b_index] = 0.1;
        for(int a_index = 0; a_index < a_size; a_index++)
            a[a_index] = network.getLayerarr()[i - 1].getNeuronarr()[a_index].getActivatedValue();
        //calculate z and call activate function
        for(int j = 0; j < neuroncounts[i]; j++){
            z[j] = 0;
            for(int k = 0; k < neuroncounts[i - 1]; k++){
                //z_j += w_jk * a_k
                z[j] += w[j * neuroncounts[i - 1] + k] * a[k];
            }
            z[j] += b[j];
            network.getLayerarr()[i].getNeuronarr()[j].setValue(z[j]);
            network.getLayerarr()[i].getNeuronarr()[j].activate();
        }

        delete [] w;
        delete [] b;
        delete [] z;
        delete [] a;
    }

    for(int i = 0; i < layercount; i++){
        cout << "Layer " << i << ":" << endl;
        for(int j = 0; j < neuroncounts[i]; j++){
            cout << network.getLayerarr()[i].getNeuronarr()[j].getActivatedValue() << endl;
        }
    }
    delete [] neuroncounts;
    delete [] neurontypes;
    delete [] inputs;
    return EXIT_SUCCESS;
}