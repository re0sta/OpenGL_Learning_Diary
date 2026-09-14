	#version 330 core								
			out vec4 FragColor;				
		in vec4 vertexColor;	
		in vec2 texCoord;
		uniform sampler2D ourTexture1;//uniform sampler将当前context中的GL_TEXTURE_2D自动传入
		uniform sampler2D ourTexture2;
		void main()							
		{FragColor=mix(texture(ourTexture1,texCoord),texture(ourTexture2,texCoord),0.2);}			
