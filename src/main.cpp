/* main.cpp
 *
 * Copyright (C) 2019-2020 Космическое П. <kosmospredanie@yandex.ru>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "config.hpp"
#include "assets.hpp"
#include "globals.hpp"
#include "app.hpp"
#include <TGUI/TGUI.hpp>
#include "startscene.hpp"

using namespace std;
using namespace sf;

namespace {
	tgui::Theme _theme;

	constexpr float getScaleToFit (const Vector2f &windowSize, const Vector2f &worldSize) {
		float windowRatio = windowSize.y / windowSize.x;
		float worldRatio = worldSize.y / worldSize.x;
		return windowRatio > worldRatio ? windowSize.x / worldSize.x : windowSize.y / worldSize.y;
	}

	void resize (RenderWindow &window, unsigned int width, unsigned int height) {
		window.setView( View(FloatRect(0, 0, width, height)) );

		yakblt::App &app = yakblt::app();
		Vector2f size = Vector2f(width, height);
		app.background().setContentSize(size);

		Vector2f worldSize = Vector2f(WORLD_WIDTH, WORLD_HEIGHT);
		float scale = getScaleToFit(size, worldSize);
		worldSize *= scale;
		Vector2f pos = Vector2f((width - worldSize.x) / 2, (height - worldSize.y) / 2);
		app.root().setPosition(pos);
		app.root().setScale(scale, scale);
	}

	void initWindow () {
		VideoMode mode(WINDOW_WIDTH, WINDOW_HEIGHT);
		RenderWindow *window = new RenderWindow(mode, TITLE);
		window->setVerticalSyncEnabled(VSYNC);
		window->setFramerateLimit(FRAMERATE);
		yakblt::setWindow(*window);
	}

	void initApp () {
		yakblt::App *app = new yakblt::App( yakblt::window() );
		yakblt::setApp(*app);
		const Vector2f &view = app->window().getView().getSize();
		resize(app->window(), view.x, view.y);
	}

	void initGuiTheme () {
		_theme = tgui::Theme(GUI_THEME);
		tgui::Theme::setDefault(&_theme);
	}

	void initScene () {
		initGuiTheme();
		yakblt::StartScene *scene = new yakblt::StartScene();
		yakblt::app().replaceScene(scene);
	}

	void handleEvent (RenderWindow &window, Event &event) {
		switch (event.type) {
		case Event::Closed:
			window.close();
			break;
		case Event::Resized:
			resize(window, event.size.width, event.size.height);
			break;
		default:
			break;
		}
		yakblt::app().onSfmlEvent().fireEvent(event);
	}

	void render (RenderWindow &window) {
		window.clear();
		yakblt::app().render(window);
		window.display();
	}

	void loop () {
		RenderWindow &window = yakblt::window();
		while ( window.isOpen() ) {
			Event event;
			while ( window.pollEvent(event) ) {
				handleEvent(window, event);
			}
			render(window);
		}
	}

	void dispose () {
		yakblt::App *app = &yakblt::app();
		delete app;
		RenderWindow *window = &yakblt::window();
		delete window;
	}
}

int main () {
	initWindow();
	initApp();
	initScene();
	loop();
	dispose();
	return 0;
}
