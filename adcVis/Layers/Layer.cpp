#include "Layer.h"


// Initialize static members
unsigned int	Layer::layerCount = 0;
GLfloat		Layer::outlineOffset = 1.0;


Layer::Layer()
{
	layerCount++;
	layerID = layerCount;

	numNodes = 0;
	numElements = 0;
	numTimesteps = 0;

	minX = 0.0;
	maxX = 0.0;
	minY = 0.0;
	maxY = 0.0;
	minZ = 0.0;
	maxZ = 0.0;

	selectedNode = 0;
	selectedElement = 0;

	vaoID = 0;
	vboID = 0;
	iboID = 0;
	outlineShader = 0;
	fillShader = 0;
	offsetValue = 0.0;
}


/**
 * @brief Used to draw the layer in the OpenGL context.
 *
 * This function first checks that data has been loaded to the OpenGL context and that
 * both shaders have been set before binding the Layer's vertex array object and
 * drawing the Layer.
 *
 * If a subclassed Layer needs to draw more (eg. selected nodes or elements), simply
 * override this function, call Layer::Draw(), and perform drawing operations. This function
 * does not unbind the vertex array after draw operations.
 *
 */
void Layer::Draw()
{
	if (glLoaded && outlineShader != 0 && fillShader != 0 && vaoID != 0)
	{
		glBindVertexArray(vaoID);

		// Draw Fill
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glPolygonOffset(offsetValue + 1, offsetValue + 1);
		if (fillShader->Use() == 0)
			glDrawElements(GL_TRIANGLES, numElements*3, GL_UNSIGNED_INT, (GLvoid*)0);

		// Draw Outline
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glPolygonOffset(offsetValue, offsetValue);
		if (outlineShader->Use() == 0)
			glDrawElements(GL_TRIANGLES, numElements*3, GL_UNSIGNED_INT, (GLvoid*)0);
	}
}


/**
 * @brief Used to inform the Layer object that the current timestep has
 * changed.
 *
 * This function is meant to be overridden by subclasses of Layer that need to know the
 * current timestep (eg. water layers). Default behavior is to do nothing.
 *
 * @param timestep The new current timestep.
 */
void Layer::UpdateTimestep(int timestep)
{
	(void)timestep;
	return;
}


/**
 * @brief Returns the unique ID associated with the Layer object.
 * @return The unique ID associated with the Layer object.
 */
unsigned int Layer::GetID()
{
	return layerID;
}


/**
 * @brief Returns the total number of Layer objects that have
 * been created.
 * @return The total number of Layer objects that have been created.
 */
unsigned int Layer::GetNumLayers()
{
	return layerCount;
}


/**
 * @brief Returns the smallest x-coordinate.
 * @return The minimum x-coordinate in Layer::nodes
 */
float Layer::GetMinX()
{
	return minX;
}


/**
 * @brief Returns the largest x-coordinate.
 * @return The maximum x-coordinate in Layer::nodes
 */
float Layer::GetMaxX()
{
	return maxX;
}


/**
 * @brief Returns the smallest y-coordinate.
 * @return The minimum y-coordinate in Layer::nodes
 */
float Layer::GetMinY()
{
	return minY;
}


/**
 * @brief Returns the largest y-coordinate.
 * @return The maximum y-coordinate in Layer::nodes
 */
float Layer::GetMaxY()
{
	return maxY;
}


/**
  * @brief Returns the smallest z-coordinate.
  * @return The minimum z-coordinate in Layer::nodes
  */
float Layer::GetMinZ()
{
	return minZ;
}


/**
  * @brief Returns the largest z-coordinate.
  *
  * @return The maximum z-coordinate in Layer::nodes
  */
float Layer::GetMaxZ()
{
	return maxZ;
}


/**
 * @brief Returns a pointer to the requested Node.
 *
 * This function is meant to be implemented by a subclass of Layer. Specifically,
 * Layers that are modeling terrain should typically be able to return specific
 * Nodes. Layers that are modeling water, on the other hand, will usually only
 * contain a list of z-coordinates in order to keep memory footprint low, and
 * therefore will not be able to return a Node.
 *
 * This version of the overloaded function should return the Node with the
 * given node number.
 *
 * If it is not overridden, this function will always return 0.
 *
 * @param nodeNumber The node number as defined in the fort.14 file.
 * @return A pointer to the Node object if the node number is valid.
 * @return 0 otherwise.
 */
Node* Layer::GetNode(unsigned int nodeNumber)
{
	(void)nodeNumber;
	return 0;
}


/**
 * @brief Returns a pointer to the requested Node.
 *
 * This function is meant to be implemented by a subclass of Layer. Specifically,
 * Layers that are modeling terrain should typically be able to return specific
 * Nodes. Layers that are modeling water, on the other hand, will usually only
 * contain a list of z-coordinates in order to keep memory footprint low, and
 * therefore will not be able to return a Node.
 *
 * This version of the overloaded function should return the Node closest to the
 * given (x, y) coordinatesof a mouse click in the OpenGL context.
 *
 * If it is not overridden, this function will always return 0.
 *
 * @param x The x-coordinate of the mouse click in the OpenGL context
 * @param y The y-coordinate of the mouse click in the OpenGL context
 * @return A pointer to the Node object closest to the (x, y) mouse click.
 * @return 0 otherwise.
 */
Node* Layer::GetNode(float x, float y)
{
	(void)x;
	(void)y;
	return 0;
}


/**
 * @brief Returns a pointer to the requested Element.
 *
 * This function is meant to be implemented by a subclass of Layer. Specifically,
 * Layers that are modeling terrain should typically be able to return specific
 * Elements. Layers that are modeling water, on the other hand, will usually only
 * contain a list of z-coordinates in order to keep memory footprint low, and
 * therefore will not be able to return an Element.
 *
 * This version of the overloaded function should return the Element with the
 * given element number.
 *
 * If it is not overridden, this function will always return 0.
 *
 * @param elementNumber The element number as defined in the fort.14 file.
 * @return A pointer to the Element object if the element number is valid.
 * @return 0 otherwise.
 */
Element* Layer::GetElement(unsigned int elementNumber)
{
	(void)elementNumber;
	return 0;
}


/**
 * @brief Returns a pointer to the requested Element.
 *
 * This function is meant to be implemented by a subclass of Layer. Specifically,
 * Layers that are modeling terrain should typically be able to return specific
 * Elements. Layers that are modeling water, on the other hand, will usually only
 * contain a list of z-coordinates in order to keep memory footprint low, and
 * therefore will not be able to return an Element.
 *
 * This version of the overloaded function should return the Element closest to the
 * given (x, y) coordinates of a mouse click in the OpenGL context.
 *
 * If it is not overridden, this function will always return 0.
 *
 * @param x The x-coordinate of the mouse click in the OpenGL context
 * @param y The y-coordinate of the mouse click in the OpenGL context
 * @return A pointer to the Element object closest to the (x, y) mouse click.
 * @return 0 otherwise.
 */
Element* Layer::GetElement(float x, float y)
{
	(void)x;
	(void)y;
	return 0;
}


/**
 * @brief Returns a pointer to the currently selected Node.
 *
 * This function is meant to be used by subclasses that implement Node/Element
 * picking. These subclasses should set the selectedNode variable to be a pointer
 * to the currently selected Node. This function can then be used to access that
 * pointer.
 *
 * @return A pointer to the currently selected Node
 * @return 0 if there is no currently selected Node
 */
Node* Layer::GetSelectedNode()
{
	return selectedNode;
}


/**
 * @brief Returns a pointer to the currently selected Element
 *
 * This function is meant to be used by subclass that implement Node/Element
 * picking. These subclasses should set the selectedElement variable to be a
 * pointer to the currently selected Element. This function can that be used to
 * access that pointer.
 *
 * @return A pointer to the currently selected Element
 * @return 0 if there is no currently selected Element
 */
Element* Layer::GetSelectedElement()
{
	return selectedElement;
}


/**
 * @brief Sets the outline shader.
 * @param newShader Pointer to the outline shader to be used when drawing.
 */
void Layer::SetOutlineShader(GLShader *newShader)
{
	outlineShader = newShader;
}


/**
 * @brief Sets the fill shader.
 * @param newShader Pointer to the fill shader to be used when drawing.
 */
void Layer::SetFillShader(GLShader *newShader)
{
	fillShader = newShader;
}


/**
 * @brief Sets the offset that will be used during drawing operations.
 *
 * The offset value is used to prevent z-fighting when drawing multiple layers in the same
 * OpenGL context. The glPolygonOffset function is used to slightly modify the z-values of
 * polygons during draw operations so that layers that have very similar z-values (eg. the fill
 * and outline use the exact same values to draw so z-fighting will always occur without using
 * an offset) will appear with the correct layer on top.
 *
 * The value passed in here is used to relate Layer objects to other Layer objects. Offsetting
 * the outline from the fill is done automatically using the static Layer::outlineOffset value.
 *
 * @param newOffset The new offset value.
 */
void Layer::SetOffsetValue(GLfloat newOffset)
{
	offsetValue = newOffset;
}


/**
 * @brief Transfers node and element data to the OpenGL context.
 *
 * This function is used to pass Node and Element data to the OpenGL context in order to
 * be rendered. Node location data is densely packed in order:
 * - [x1, y1, z1, 1.0, x2, y2, z2, 1.0, ...]
 * .
 * Element data is also densely packed in order:
 * - [e1n1, e1n2, e1n3, e2n1, e2n2, e2n3, ...]
 * .
 *
 * We make use of Vertex Array Objects, so once the Node data is put into a Vertex
 * Buffer Object and Element data is put into an Index Buffer Object, the OpenGL state
 * is saved in the VAO state.
 *
 * The default behavior is to create a new vertex array object if it has not been created yet
 * and to load all data from Layer::nodes and Layer::elements to the OpenGL context. Data is
 * passed in with the usage flag GL_STATIC_DRAW, so if your Layer will be frequently updating
 * data (eg. water elevation data), you should override this function and use the appropriate
 * flag.
 *
 * Once data has been loaded to the OpenGL context, the Layer::glLoaded flag is set to true.
 *
 */
void Layer::LoadDataToGPU()
{

	// Dev Note: Probably smart to check buffer sizes against video card memory size
	// because very large domains could be too large for smaller cards

	if (!glLoaded || vaoID == 0)
	{
		// Create the new VAO, VBO, and IBO
		glGenVertexArrays(1, &vaoID);
		glGenBuffers(1, &vboID);
		glGenBuffers(1, &iboID);

		// Bind the VAO so that all subsequent OpenGL binding calls are
		// saved into this VAO's state.
		glBindVertexArray(vaoID);

		// Load vertex data to the OpenGL context
		const size_t VertexBufferSize = 4*sizeof(GLfloat)*nodes.size();
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), 0);
		glBufferData(GL_ARRAY_BUFFER, VertexBufferSize, NULL, GL_STATIC_DRAW);
		GLfloat *vdataPtr = (GLfloat *)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		if (vdataPtr)
		{
			for (unsigned int i=0; i<nodes.size(); i++)
			{
				vdataPtr[4*i+0] = (GLfloat)nodes[i].x;
				vdataPtr[4*i+1] = (GLfloat)nodes[i].y;
				vdataPtr[4*i+2] = (GLfloat)nodes[i].z;
				vdataPtr[4*i+3] = (GLfloat)1.0;
			}

			if (glUnmapBuffer(GL_ARRAY_BUFFER) == GL_FALSE)
			{
				DEBUG("Error unmapping vertex buffer object in layer %i", layerID);
				return;
			}

		} else {
			DEBUG("Error mapping to vertex buffer object in layer %i", layerID);
			return;
		}

		// Load index data to the OpenGL context
		const size_t IndexBufferSize = 3*sizeof(GLuint)*elements.size();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, IndexBufferSize, NULL, GL_STATIC_DRAW);
		GLuint *idataPtr = (GLuint *)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
		if (idataPtr)
		{
			for (unsigned int i=0; i<elements.size(); i++)
			{
				idataPtr[3*i+0] = (GLuint)elements[i].n1-1;
				idataPtr[3*i+1] = (GLuint)elements[i].n2-1;
				idataPtr[3*i+2] = (GLuint)elements[i].n3-1;
			}

			if (glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER) == GL_FALSE)
			{
				DEBUG("Error unmapping index buffer object in layer %i", layerID);
				return;
			}
		} else {
			DEBUG("Error mapping to index buffer object in layer %i", layerID);
			return;
		}

		// Unbind the VAO to finish saving it's state
		glBindVertexArray(0);

		// Do one final check for OpenGL errors
		GLenum errorCheck = glGetError();
		if (errorCheck == GL_NO_ERROR)
		{
			glLoaded = true;
		} else {
			glLoaded = false;
			DEBUG("OpenGL Error found after loading data from layer %i", layerID);
		}

	}
}
