/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_VIEWPORT
#define RRE_VIEWPORT

#include <memory> // std::unique_ptr, std::make_unique
#include <mutex>
#include <vector>

#include "GameMode.hpp"
#include "Logger.hpp"
#include "Movie.hpp"
#include "Scene.hpp"
#include "Sprite.hpp"
#include "factory/MovieFactory.hpp"
#include "impl/ViewportImpl.hpp"


/**
 * Interface for rendering images.
 *
 * TODO:
 * - move rendering functions to new renderer class or Scene
 */
class Viewport: public ViewportImpl {
private:
	/** Logger instance for this class. */
	static Logger logger;

	/** Static singleton instance. */
	static std::unique_ptr<Viewport> instance;
	/** Mutex for thread safety. */
	static std::mutex mtx;

	// delete copy constructor & assignment operator for singleton
	Viewport(const Viewport&) = delete;
	Viewport& operator=(const Viewport&) = delete;

	/** Font map for drawing text. */
	FontMap* font_map;
	/** Detected FPS. */
	uint16_t current_fps;

	/**
	 * Current game mode.
	 *
	 * TODO: _maybe_ use `GameLoop.getMode` instead
	 */
	GameMode::Mode mode;

	/** Texture drawn on background during `GameMode::MENU` or `GameMode::TITLE`. */
	SDL_Texture* background;
	/** Text sprite representing RPS that can be drawn on renderer. */
	Sprite* fps_sprite;
	/** Scene rendered during `GameMode::SCENE`. */
	Scene* scene;

	/** Currently playing movie. */
	Movie* movie;

	/**
	 * Text sprite to draw on renderer.
	 *
	 * TODO: replace with text sprite class with x/y offsets
	 */
	std::vector<Sprite*> text_sprites;

public:
	/** Default constructor. */
	Viewport();

	/**
	 * Default destructor.
	 */
	~Viewport() {}

	/**
	 * Initializes & retrieves singleton instance.
	 *
	 * @return
	 *   Static singleton instance.
	 */
	static Viewport* get() {
		if (!instance) {
			std::lock_guard<std::mutex> lock(mtx); // lock for thread safety
			instance = std::make_unique<Viewport>();
		}
		return instance.get();
	}

	/** Overrides `ViweportImpl::init`. */
	void init(SDL_Window* window) override;

	/** Overrides `ViewportImpl::shutdown`. */
	void shutdown() override;

	/** Overrides `ViewportImpl::setFontMap`. */
	void setFontMap(FontMap* font_map) override { this->font_map = font_map; }

	/** Overrides `ViewportImpl::getFontMap`. */
	FontMap* getFontMap() override { return this->font_map; }

	/**
	 * Updates FPS value.
	 *
	 * @param fps
	 *   Detected FPS.
	 */
	void setCurrentFPS(uint32_t fps) override;

	/**
	 * Sets scaling factor of game window.
	 *
	 * @param scale
	 *   New scaling factor.
	 */
	void setScale(uint16_t scale);

	/**
	 * Unsets background texture.
	 */
	void unsetBackground();

	/**
	 * Sets background texture to draw.
	 *
	 * @param rdpath
	 *   Path to image file relative to data directory (excluding .png suffix).
	 * @return
	 *   `true` if a texture was set.
	 */
	bool setBackground(std::string rdpath);

	/**
	 * Unsets scene data.
	 *
	 * TODO: move scene methods to `GameVisuals`
	 */
	void unsetScene();

	/**
	 * Sets current scene data.
	 *
	 * @param id
	 *   Scene identifier.
	 * @return
	 *   `true` if scene was set.
	 */
	bool setScene(std::string id);

	/**
	 * Retrieves current scene.
	 *
	 * @return
	 *   Active scene instance.
	 */
	Scene* getScene() { return scene; }

	/**
	 * Sets drawing mode.
	 *
	 * TODO: rename to "setDrawMode"
	 *
	 * @param mode
	 *   Game mode use to determine how to execute drawing instructions.
	 */
	void setMode(GameMode::Mode mode);

	/** Overrides `ViewportImpl::drawTexture`. */
	void drawTexture(SDL_Texture* texture, SDL_Rect s_rect, SDL_Rect t_rect, SDL_RendererFlip flags) override;

	/**
	 * Calls `ViewportImpl::drawTexture`.
	 *
	 * NOTE: why must this be explicitly declared?
	 */
	void drawTexture(SDL_Texture* texture, SDL_Rect s_rect, SDL_Rect t_rect) {
		ViewportImpl::drawTexture(texture, s_rect, t_rect);
	}

	/** Overrides `ViewportImpl::drawImage`. */
	void drawImage(Image* img, uint32_t sx, uint32_t sy, uint32_t s_width,
			uint32_t t_height, uint32_t x, uint32_t y, SDL_RendererFlip flags) override;

	/** Overrides `ViewportImpl::drawImage`. */
	void drawImage(Image* img, uint32_t x, uint32_t y, SDL_RendererFlip flags) override;

	/**
	 * Calls `ViewportImpl::drawImage`.
	 *
	 * NOTE: why must this be explicitly declared?
	 */
	void drawImage(Image* img, uint32_t x, uint32_t y) {
		ViewportImpl::drawImage(img, x, y);
	}

	/**
	 * Renders the current scene, movie, menu, etc. on viewport.
	 */
	void render() override;

	/**
	 * Adds a text sprite to be drawn in viewport.
	 *
	 * @param text
	 *   Text value.
	 */
	void addText(std::string text);

	/**
	 * Clears all text sprites from viewport.
	 */
	void clearText();

private:
	/**
	 * Renders current scene on viewport.
	 *
	 * TODO: replace with methods in Scene class
	 */
	void drawScene();

	/** Renders current background image on viewport. */
	void drawBackground();

	/** Renders current foreground image on viewport. */
	void drawForeground();

	/** Renders configured title menu on viewport. */
	void drawTitle();

	/** Renders text sprites on viewport. */
	void drawText();

	/** Renders FPS text sprite on viewport. */
	void drawFPS();
};

#endif /* RRE_VIEWPORT */
