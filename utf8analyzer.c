#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>


int32_t is_ascii(char str[]) {
   for (int i = 0; str[i] != '\0'; i++){
       if ((unsigned char) str[i] > 127) {
           return 0;
       }
   }
   return 1;
}


int32_t capitalize_ascii(char str[]) {
   int indexing = 0;
   int32_t char_update = 0;


   while ((unsigned char)str[indexing] != 0) {
       if((unsigned char)str[indexing] >= 97 && (unsigned char)str[indexing] <= 122) {
           str[indexing] = (unsigned char)str[indexing] - 32;
           char_update++;
       }
       indexing++;
   }
   return char_update;
}


int32_t width_from_start_byte(unsigned char start_byte){


   if ((start_byte & 0x80) == 0){
       return 1;
   }
   else if ((start_byte & 0xE0) == 0xC0){
       return 2;
   }
   else if ((start_byte & 0xF0) == 0xE0){
       return 3;
   }
   else if ((start_byte & 0xF8) == 0xF0){
       return 4;
   }
   else {
       return -1;
   }
}


int32_t utf8strlen(char str[]){
   int32_t length_of = 0;
   int indexing = 0;


   while (str[indexing] != 0){
       int32_t width_of = width_from_start_byte(str[indexing]);
       if (width_of < 0){
           return -1;
       }


       for (int i = 1; i < width_of; i++){
           if ((unsigned char)str[indexing + i] == '\0' ||
               ((unsigned char)str[indexing + i] & 0xC0) != 0x80){
                   return -1;
           }
          
       }
       indexing += width_of;
       length_of++;
   }
   return length_of;
}


int32_t codepoint_index_to_byte_index(char str[], int32_t cpi){
   int32_t indexing = 0;
   int32_t codepoint = 0;


   while (str[indexing] != 0){
       int32_t width_of = width_from_start_byte(str[indexing]);
       if (width_of < 0){
           return -1;
       }
       if (codepoint == cpi){
           return indexing;
       }
       indexing += width_of;
       codepoint++;
   }
   return -1;
}


int32_t codepoint_index_to_byte_index(char str[], int32_t cpi);
int32_t width_from_start_byte(unsigned char start_byte);


void utf8_substring(char str[], int32_t cpi_start, int32_t cpi_end, char result[]) {
  
   if (cpi_start < 0 || cpi_end < 0 || cpi_start > cpi_end) {
       return;
   }
   int32_t start_byte_index = codepoint_index_to_byte_index(str, cpi_start);
   int32_t end_byte_index = codepoint_index_to_byte_index(str, cpi_end);


   if (start_byte_index == -1 || end_byte_index == -1) {
       return;
   }


   int32_t i = 0;
   for (int32_t j = start_byte_index; j < end_byte_index && str[j] != '\0'; j++) {
       result[i] = str[j]; // Copy the byte
       i++;
   }


   result[i] = '\0'; // Null terminator
}




int32_t codepoint_at(char str[], int32_t cpi) {
   int32_t current_cpi = 0; // Current codepoint index
   int i = 0; // Byte index


   while (str[i] != '\0') {
       if (current_cpi == cpi) {
           unsigned char first = str[i];


           if ((first & 0x80) == 0) {
               return first;
           }
          
           else if ((first & 0xE0) == 0xC0) {
               return ((first & 0x1F) << 6) | (str[i + 1] & 0x3F);
           }
          
           else if ((first & 0xF0) == 0xE0) {
               return ((first & 0x0F) << 12) | ((str[i + 1] & 0x3F) << 6) | (str[i + 2] & 0x3F);
           }
         
           else if ((first & 0xF8) == 0xF0) {
               return ((first & 0x07) << 18) | ((str[i + 1] & 0x3F) << 12) | ((str[i + 2] & 0x3F) << 6) | (str[i + 3] & 0x3F);
           }
       }


     
       if ((str[i] & 0x80) == 0) {  // 1-byte character
           i += 1;
       } else if ((str[i] & 0xE0) == 0xC0) { 
           i += 2;
       } else if ((str[i] & 0xF0) == 0xE0) { 
           i += 3;
       } else if ((str[i] & 0xF8) == 0xF0) { 
           i += 4;
       }


       current_cpi++;
   }


   return -1;
}


int32_t codepoint_at(char str[], int32_t cpi);




char is_animal_emoji_at(char str[], int32_t cpi) {
   int32_t codepoints = codepoint_at(str, cpi);
  
  
   if (codepoints >= 0x1F000 && codepoints <= 0x1F9F3) { // 🐀 to 🐿️
       return 1; // it is an animal emoji
   }
   if (codepoints >= 0x1F980 && codepoints <= 0x1F9CC) { // 🦀 to 🦮
       return 1; // it is an animal emoji
   }
   return 0; // it is not an animal emoji
}




int main() {
   unsigned char input[100];
// Read input string
fgets((char*)input, sizeof(input), stdin);




// Remove trailing newline if present
size_t len = strlen((char*)input);
if (len > 0 && input[len-1] == '\n') {
   input[len-1] = '\0';
}




// Now print valid ASCII status on a new line
if (is_ascii((char*)input)) {
   printf("Valid ASCII: true\n");
} else {
   printf("Valid ASCII: false\n");
}


   // Uppercase ASCII characters
   int32_t updated_chars = capitalize_ascii((char*)input);
   printf("Uppercased ASCII: \"%s\"\n", input);




   // Length in bytes
   int total_bytes = strlen((char*)input);
   printf("Length in bytes: %d\n", total_bytes);




   // # of UTF-8 code points
   int32_t codepoint_count = utf8strlen((char*)input);
   if (codepoint_count == -1) {
       printf("Invalid UTF-8 string\n");
       return 1;
   }
   printf("Number of code points: %d\n", codepoint_count);




   // Bytes per code point
   printf("Bytes per code point: ");
   for (int i = 0; input[i] != '\0';) {
       int32_t width = width_from_start_byte(input[i]);
       printf("%d ", width);
       i += width;
   }
   printf("\n");




   // Substring of the first 6 codepoints
   char result[50];
   utf8_substring((char*)input, 0, 6, result);
   printf("Substring of the first 6 code points: \"%s\"\n", result);




   // Code points as decimal numbers
   printf("Code points as decimal numbers: ");
   for (int i = 0; i < codepoint_count; i++) {
       printf("%d ", codepoint_at((char *)input, i));
   }
   printf("\n");




   // Animal emoji check
   printf("Animal emojis: ");
   for (int i = 0, byte_index = 0; i < codepoint_count; i++) {
       if (is_animal_emoji_at((char*)input, i)) {
           int32_t width = width_from_start_byte(input[byte_index]);
           for (int j = 0; j < width; j++) {
               printf("%c", input[byte_index + j]);
           }
           printf(" "); // Space between emojis
       }
       byte_index += width_from_start_byte(input[byte_index]); // Move to next codepoint
   }
   printf("\n");




   return 0;
}



