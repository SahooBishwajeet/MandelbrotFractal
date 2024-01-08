#include <SDL2/SDL.h>
#include <numeric>
#include <complex>

// Mandelbrot Number is of the form "Z = Z**2 + c" or "Z = pow(Z,2) + c"
int isInMandelbrotSet(std::complex<double> c){
    std::complex<double> z(0,0);
    for (int i = 0; i < 50; i++) {      // Change i < __ To Increase the Quality of render
        z = std::pow(z,2) + c;

        // Using Norm Function to check for the bounds, which returns the squared magnitude of the Complex number 'z'
        if(std::norm(z) > 16)           // 16 is completely arbitrary
            return i;                   
        // Returning 'i' will give us # of Iterations it took to go out of the bounds of Mandelbrot Set, which will decide the color of the pixel
    }
    return 0;
}

int main(int argc, char const *argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_CreateWindowAndRenderer(1000,1000,0, &window, &renderer);

    // Looping Over x & y, And it will check if the current comple number is a Maldelbrot Number or Not
    // Manderbrot Number is of the form "Z = Z**2 + c" or "Z = pow(Z,2) + c"
    for (double x = 0.0; x < 1.0; x += 0.001){
        for(double y = 0.0; y < 1.0; y += 0.001){
            double pointX = std::lerp(-3.0, 3.0, x);     // Computes the Linear Interpolation b/w [a,b], which will give us the points we want to check for the x-axis
            double pointY = std::lerp(-3.0, 3.0, y);     // Computes the Linear Interpolation b/w [a,b], which will give us the points we want to check for the y-axis

            int iterations = isInMandelbrotSet(std::complex<double>(pointX, pointY));
            if(iterations == 0){
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderDrawPointF(renderer, x * 1000, y * 1000);
            }
            else{
                SDL_SetRenderDrawColor(renderer, 255 - iterations, 255 - iterations, 255 - iterations, 255);
                SDL_RenderDrawPointF(renderer, x * 1000, y * 1000);
            }
        }
    }

    SDL_RenderPresent(renderer);
    SDL_Delay(10000);

    return 0;
}
