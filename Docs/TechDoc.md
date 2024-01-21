# ReBound Code Doc
This Document will cover code conventions and organization for the ReBound game engine.
# Code Editor
- Tabs are set to two spaces to be consistent between text editors
- Includes for files within the same project use ""
- Includes from third party files of any king use <>
- All code must be inside of the main namespace RB or child of this
- Avoid global variables, keep data contained in classes or structs
# Classes
## Structure
Classes will be organized to have the most relevant API information at the top of the class.

**Static Classes may have a private _Constructor or _Destructor and must mark a friend class of Application where they can be called during the runtime of the application**

- Public:
	- Events
	- Builder
	- Methods:
		- Standard Methods
		- Virtual Methods
		- Getters
		- Setters
- Public Static:
	- Static Methods
	- Const Variables
- Private:
	- TypeDefs
	- Friend Classes
- Private Static:
	- Methods
	- Variables
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
	- Enums that support bit flags will be named as a plural I.E. Payload (No Flags), Payloads (Flags)
- Misc:
	- Type Defs will be made with the using X = Type;
## API Definitions
- Builders:
	- Structs use to instantiate engine assets with settings and may interpret platforms
	- If a builder is present, use before any other means of class instantiation
	- Example Texture::Builder().setType(TextureType::e2D).Build()
- Ref:
	- Refs are wrapped shared_ptr's mainly used by assets
	- If a Ref is need the class will provide a builder for creation
- Scope:
	- Scopes are wrapped unique_ptr's
	- Mainly used to store singleton's that shouldn't be duplicated anyways
- Object:
	- Object class can be inherited by any class to help the compiler know it should support reflection
	- Object classes in the main engine must be registered on the Reflection/Domain
	- Object class MetaInfo can be acquired from the Domain to gain runtime information
- Component:
	- Similar to the object class but supports specifically components for entities
	- Components are also registered to Reflection/Domain
	- Component class MetaInfo can be acquired from the Domain for runtime information