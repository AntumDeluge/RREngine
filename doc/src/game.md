
# Game Configuration

_This project is in early development stages & not yet fully functional. Documentation may be
incomplete._

## Configuration Files

Games are configured using [XML files](https://wikipedia.org/wiki/XML) located in the `data/conf`
subdirectory where engine executable is located.

### game.xml

This is the main configuration file. It must have a root `game` node. The following nested nodes
are supported:

- __title:__ Text displayed in window title bar.
- __icon:__ Icon displayed in window title bar _(not yet supported)_.
- __scale:__ Window scaling factor. Max 4.
- __step_delay:__ Game stepping delay in milliseconds.
- __intro:__ Configures the introduction movie. Attributes:
    - __movie:__ Movie played in introduction. Configured in [movies.xml](#moviesxml).
- __menu:__ Configured main menu. Attributes:
    - __id:__ Menu identifier.
    - __background:__ Menu background image. Images located in `data/background` directory.
    - __music:__ Menu music. See [music](#music).

### sprites.xml

Configures entity sprites. Must contain a `sprites` root node. Each sprite is configured in a
`sprite` node. Each sprite must have an `id` attribute. The following nested nodes are supported:

- __filename:__ Base filename of sprite image. Attributes:
    - __index:__ Used for static sprites.
- __size:__ Sprite frame dimensions. Supports `width` & `height` attributes.
- __animation:__ Animation definition. Supports `mode` attribute to identify each animation mode.
  Nested `frame` nodes are used to define a frame of animation using `index` & `delay` attributes.

Example:

```xml
<sprites>

	<sprite id="player">
		<filename>character</filename>
		<size width="32" height="32" />
		<animation mode="idle" default="true">
			<frame index="6" delay="4000" />
			<frame index="7" delay="250" />
		</animation>
		<animation mode="run">
			<frame index="10" delay="100" />
			<frame index="9" delay="100" />
			<frame index="10" delay="100" />
			<frame index="11" delay="100" />
		</animation>
		<animation mode="fall">
			<frame index="0" delay="10000" />
		</animation>
	</sprite>

	<sprite id="enemy">
		<filename>enemy</filename>
		<size width="16" height="16" />
		<animation mode="idle" default="true">
			<frame index="0" delay="4000" />
			<frame index="1" delay="250" />
		</animation>
		<animation mode="run">
			<frame index="6" delay="100" />
			<frame index="7" delay="100" />
			<frame index="8" delay="100" />
			<frame index="7" delay="100" />
		</animation>
		<animation mode="fall">
			<frame index="3" delay="10000" />
		</animation>
	</sprite>

	<sprite id="flying_enemy">
		<filename>flying_enemy</filename>
		<size width="22" height="24" />
		<animation mode="idle" default="true">
			<frame index="0" delay="250" />
			<frame index="1" delay="250" />
		</animation>
	</sprite>

</sprites>
```

### entities.xml

Configures all the entities available in the game. Must contain a root `entities` node.

Example:

```xml
<entities>

	<entity id="player" sprite="player" width="18" height="23">
		<momentum>3.0</momentum>
	</entity>

	<entity id="enemy" sprite="enemy" width="16" height="12">
		<momentum>1.0</momentum>
	</entity>

	<entity id="flying_enemy" sprite="flying_enemy" width="22" height="24">
		<momentum>1.0</momentum>
		<gravity>0.0</gravity>
	</entity>

</entities>
```

### scenes.xml

_Currently not supported._

### movies.xml

Example:

```xml
<movies>

	<movie id="intro" fade_in="200" fade_out="200">
		<frame ms="5000">NULL</frame>
		<text delay="0" duration="10000">Rock & Roll Engine</text>
		<text delay="0" duration="10000">(alpha)</text>
	</movie>

</movies>
```

## Scenes

Scene maps are built in the [Tiled Map Editor](https://mapeditor.org/) format & stored in the
`data/scene` directory. They are configured in [scenes.xml](#scenesxml).

The following layer names are supported:

- __weather:__ _not implemented_
- __foreground:__ Front most tile layer drawn above entities.
- __collision:__ Tiles on this layer define scene points of collision.
- __objects:__ _not implemented_
- __terrain:__ First tile layer drawn under entities.
- __background:__ Second tile layer drawn under entities.
- __s_background:__ First background image layer. Parallax scrolling supported using custom property
  `scroll_rate` float value.
- __s_background2:__ Second background image layer. Parallax scrolling also supported.

## Audio

### Sound Effects

_Currently not supported._

### Music

Music files are located in the `data/music` directory. The engine supports playing
[Ogg Vorbis](https://xiph.org/vorbis/) audio. Files must have either the `.oga` or `.ogg` filename
extension.

## Graphics

_Currently only [PNG](https://wikipedia.org/wiki/PNG) images supported._

### Sprite Images

Sprites are stored in the `data/sprite` directory. They are configured in
[sprites.xml](#spritesxml).

### Tilesets

Scene tileset images are located in `data/tileset` by default. Storing in other locations may work
but not officially supported. These tilesets are used for creating [scene maps](#scenes).
