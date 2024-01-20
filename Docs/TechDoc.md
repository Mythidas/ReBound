# ReBound Code Doc
This Document will cover code conventions and organization for the ReBound game engine.
# Classes
## Structure
Classes will be organized to have the most relevant API information at the top of the class.
- Public:
	- Events
	- Builder
	- Methods:
		- Standard Methods
		- Virtual Methods
		- Getters
		- Setters
	- Static Methods
	- Const Variables
- Private:
	- Methods
	- Variables
## Naming
- Classes & Structs:
	- Names will start with a capital letter
	- Platform specific classes will begin with the platform I.E. OGL_Texture for and OpenGL Texture
- Variables:
	- Private Member Variables will be prefixed with m_
	- Private Static Variables will be prefixed with s_
	- Public Const Variables will be fully capitalized
- Methods:
	- Public Methods will be First Letter Capital with Camel Case I.E. GetMainWindow()
	- Private Methods will follow the same rules and be prefixed with _ I.E. _GetMainWindow()
- Enums:
	- Enums will be plainly types I.E. None, Filled, Spotted
	- Numerical enums will prefixed with e I.E. e1D, e2D, e3D
	- Enums that support bit flags will be suffixed with s I.E. Payload (No Flags), Payloads (Flags)
## API
Neeed to add this**