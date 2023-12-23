cmake_minimum_required(VERSION 3.11)

project(
  gigperformer_sdk
  VERSION 4.7
  DESCRIPTION "API for Gig Performer extension development"
  HOMEPAGE_URL "https://www.gigperformer.com"
  LANGUAGES C CXX)

add_subdirectory(c)
add_subdirectory(cpp)
