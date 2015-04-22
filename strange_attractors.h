////////////////////////////////////////////////////////////////////////////////
//
// (C) Andy Thomason 2012-2014
//
// Modular Framework for OpenGLES2 rendering on multiple platforms.
//

#include <Windows.h>
#include <iostream>
#include <math.h>
#include <gl/GLU.h>


namespace octet {


	/// Scene containing a box with octet.
	class strange_attractors : public app {

		ref<visual_scene> app_scene;

		// helper for drawing text
		ref<text_overlay> overlay;

		// text mesh object for overlay.
		ref<mesh_text> text;


	public:
		/// this is called when we construct the class before everything is initialised.
		strange_attractors(int argc, char **argv) : app(argc, argv) {
		}

		dynarray<float> vertices_x;
		dynarray<float> vertices_y;
		dynarray<float> vertices_z;

		int point = 0; //current iteration
		int counter = 0; //how many iterations to go through in one frame
		int number = 0;
		bool drawn = false; //whether the attractor is finished drawing
		bool lorenz = false; //whether the attractor requires line drawing or just points
		int increment = 100;

		int	iterations = 100000; // number of times to iterate through the algorithm
		float x, y, z, a, b, c, d; //variables for formulas
	
		/// this is called once OpenGL is initialized
		void app_init() {

			//load app_scene and bring up king's dream attractor on start up
			start();
			app_scene->get_camera_instance(0)->get_node()->translate(vec3(0, 0, -30));
			draw_kings_dream();
			
		}

		void start(){
			app_scene = new visual_scene();
			app_scene->create_default_camera_and_lights();
			app_scene->get_camera_instance(0)->set_far_plane(100000);

			material *black = new material(vec4(0, 0.3, 0.3, 1));
			mesh_box *box = new mesh_box(vec3(500, 500, 500));
			scene_node *node = new scene_node();
			app_scene->add_child(node);
			app_scene->add_mesh_instance(new mesh_instance(node, box, black));
	
		}


		void draw_kings_dream(){

			x = 0.1;
			y = 0.1;		// starting point
			a = -0.966918;		// coefficients for "The King's Dream"
			b = 2.879879;
			c = 0.765145;
			d = 0.744728;


			// go through the equations many times, drawing a point for each iteration
			for (int i = 0; i < iterations; i++) {

				// compute a new point using the strange attractor equations
				float xnew = sin(y*b) + c*sin(x*b);
				float ynew = sin(x*a) + d*sin(y*a);

				// save the new point
				x = xnew;
				y = ynew;

				//add points to dynamic array of coordinates
				vertices_x.push_back(x);
				vertices_y.push_back(y);
				vertices_z.push_back(0);
			}
		}

		void draw_henon(){

			x = 1;
			y = 1;		// starting point coefficients for "Henon" attractor
			

			// go through the equations many times, drawing a point for each iteration
			for (int i = 0; i < iterations; i++) {

				// compute a new point using the strange attractor equations
				float xnew = y + 1 - (1.4*x*x);
				float ynew = 0.3*x;

				// save the new point
				x = xnew;
				y = ynew;

				//add points to dynamic array of coordinates
				vertices_x.push_back(x);
				vertices_y.push_back(y);
				vertices_z.push_back(0);
			}
		}

		void draw_lorenz(){

			x = 1; y = 1; z = 1;		// starting point
			a = 10;		// coefficients for "The Lorenz attractor"
			b = 28;
			c = 8 / 3;


			// go through the equations many times, drawing a point for each iteration
			for (int i = 0; i < iterations; i++) {

				//compute a new point using strange attractor equations
				float dt = 0.015;
				float newx = x - (a*x*dt) + (a*y*dt);
				float newy = y + (b*x*dt) - (y*dt) - (z*x*dt);
				float newz = z - (c*z*dt) + (x*y*dt);// save the new point

				//save  the new point
				x = newx;
				y = newy;
				z = newz;

				//add the point to dynamic array of coordinates
				vertices_x.push_back(x);
				vertices_y.push_back(y);
				vertices_z.push_back(z);

			}
		}

			void draw_rossler(){

				x = 0.1; y = 0.1; z = 0.1;		// starting point
				a = 0.2;		// coefficients for "The Rossler attractor"
				b = 0.2;
				c = 5.7;

				// go through the equations many times, drawing a point for each iteration
				for (int i = 0; i < iterations; i++) {

					//compute point using strange attractor equations
					float dt = 0.015;
					float xDelta = dt*(-y - z);
					float newx = x + xDelta;
					float yDelta = dt*(x + a*y);
					float newy = y + yDelta;
					float zDelta = dt*(b + z*(x - c));
					float newz = z + zDelta;

					//save new point
					x = newx;
					y = newy;
					z = newz;

					//add new point to dynamic array of coodinates
					vertices_x.push_back(x);
					vertices_y.push_back(y);
					vertices_z.push_back(z);

				}
		}

		void draw_tinkerbell(){


			x = -0.72; y = -0.64; 		// starting point
			a = 0.9;		// coefficients for "The Tinkerbell chaotic map"
			b = -0.6013;
			c = 2;
			d = 0.5;

			// go through the equations many times, drawing a point for each iteration
			for (int i = 0; i < iterations; i++) {

				//compute new point using strange attractor equations
				float newx = (x*x) - (y*y) + (a*x) + (b*y);
				float newy = (2 * x*y) + (c*x) + (d*y);

				//save new poinr
				x = newx;
				y = newy;

				//add new point to dynamic array of coordinates
				vertices_x.push_back(x);
				vertices_y.push_back(y);
				vertices_z.push_back(0);
			}
		}

		void draw_gingerbreadman(){


			x = -1.1; y = 1; 		// starting point coefficients for "gingerbread man" attractor

			// go through the equations many times, drawing a point for each iteration
			for (int i = 0; i < iterations; i++) {

				//compute new point using equation
				float newx = 1 - y + abs(x);
				float newy = x;

				//save new point
				x = newx;
				y = newy;

				//add point to dynamic array of coordinates
				vertices_x.push_back(x);
				vertices_y.push_back(y);
				vertices_z.push_back(0);
			}


		}



		/// this is called to draw the world
		void draw_world(int x, int y, int w, int h) {

			int vx = 0, vy = 0;
			get_viewport_size(vx, vy);
			app_scene->begin_render(vx, vy);

			if (is_key_down(key_up)){
				app_scene->get_camera_instance(0)->get_node()->translate(vec3(0, 0, -5));
			}
			if (is_key_down(key_down)){
				app_scene->get_camera_instance(0)->get_node()->translate(vec3(0, 0, 5));
			}
			//run new attractor depending on button pressed
			if (is_key_down('A')){
				app_scene->reset();
				counter = 0;
				lorenz = true;
				iterations = 10000;
				increment = 3;
				vertices_x.reset(); vertices_y.reset(); vertices_z.reset();
				start();
				app_scene->get_camera_instance(0)->get_node()->translate(vec3(2, 0, 70));
				draw_lorenz();
			}


			if (is_key_down('B')){

				app_scene->reset();
				counter = 0;
				lorenz = false;
				iterations = 100000;
				increment = 100;
				vertices_x.reset(); vertices_y.reset(); vertices_z.reset();
				start();
				app_scene->get_camera_instance(0)->get_node()->translate(vec3(0, 0, -30));
				draw_kings_dream();

			}

			if (is_key_down('C')){

				app_scene->reset();
				counter = 0;
				lorenz = false;
				iterations = 100000;
				increment = 100;
				vertices_x.reset(); vertices_y.reset(); vertices_z.reset();
				start();
				app_scene->get_camera_instance(0)->get_node()->translate(vec3(0, -0.5, -31.5));
				draw_tinkerbell();

			}

			if (is_key_down('D')){

				app_scene->reset();
				counter = 0;
				lorenz = false;
				iterations = 100000;
				increment = 100;
				vertices_x.reset(); vertices_y.reset(); vertices_z.reset();
				start();
				app_scene->get_camera_instance(0)->get_node()->translate(vec3(2, -1, -15));
				draw_gingerbreadman();

			}

			if (is_key_down('E')){

				app_scene->reset();
				counter = 0;
				lorenz = true;
				iterations = 10000;
				increment = 15;
				vertices_x.reset(); vertices_y.reset(); vertices_z.reset();
				start();
				app_scene->get_camera_instance(0)->get_node()->translate(vec3(0, 0, 10));
				draw_rossler();
			}

			if (is_key_down('F')){

				app_scene->reset();
				counter = 0;
				lorenz = false;
				iterations = 100000;
				increment = 100;
				vertices_x.reset(); vertices_y.reset(); vertices_z.reset();
				start();
				app_scene->get_camera_instance(0)->get_node()->translate(vec3(0, 0, -32));
				draw_henon();

			}

			//for animation
			if (counter <= iterations){

				while (point < counter - 1){

					glLineWidth(1.0);

					//either draw line or point 
					if (lorenz == true){
						glBegin(GL_LINES);
					}
					else if (lorenz == false) { glBegin(GL_POINTS); }

					//use dynamic array to plot points each frame
					glVertex3f(vertices_x[point], vertices_y[point], vertices_z[point]);
					glVertex3f(vertices_x[point + 1], vertices_y[point + 1], vertices_z[point + 1]);
					glEnd();
					point++;
				}


				if (drawn == false){
					counter += increment;
				}

				if (counter > iterations){
					drawn = true;
				}

				if (drawn == true){
					counter = iterations;
				}
			}

			//return point to 0 for fresh start next frame
			point = 0;


			// update matrices. assume 30 fps.
			app_scene->update(1.0f / 30);

			// draw the scene
			app_scene->render((float)vx / vy);


			// enable blending
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			// enable point smoothing
			glEnable(GL_POINT_SMOOTH);
			glPointSize(1.0f);


		}
	};
}
