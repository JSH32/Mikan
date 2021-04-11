/**
 * @file util.h
 * @brief Random utility functions for things like image loading
 */

#pragma once

#include <glad/glad.h>

/**
 * @brief Load an image from a buffer to a GL texture
 */
bool loadTextureFromImage(unsigned char* buffer, int size, GLuint& out, int& w, int& h);