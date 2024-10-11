/*
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>



int32_t is_ascii(char str[]) {
   for (int i = 0; str[i] != ‘\0’; i++){
       if ((unsigned char) str[i] > 127) {
           return 0;
       }
   }
   return 1;
}


//Testing
int main() {
   printf("Is 🔥 ASCII? %d\n", is_ascii("🔥"));
   printf("Is abcd ASCII? %d\n", is_ascii("abcd"));
  
   return 0;
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


  
int main() {
   int32_t ret = 0;
   char str[] = "abcd";
   ret = capitalize_ascii(str);
   printf("Capitalized String: %s\nCharacters updated: %d\n", str, ret);


   return 0;
}



int32_t width_from_start_byte(char start_byte) {


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


int main() {
   char s[] = "Héy";


   printf("Width: %d bytes\n", width_from_start_byte(s[1]));
   printf("Width: %d bytes\n", width_from_start_byte(s[2]));


   return 0;
}




int32_t utf8strlen(char str[]){
   int32_t length_of = 0;
   int indexing = 0;


   while (str[indexing] != 0){
       int32_t width_of = width_from_start_byte(str[index]);
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


int main() {
   char str[] = "Joséph";
   printf("Length of string '%s' is %d\n", str, utf8_strlen(str));
   return 0;


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


int main() {
   char str[] = "Joséph";
   int32_t idx = 4;


   int32_t byte_index = codepoint_index_to_byte_index(str, idx);
   printf("Codepoint index %d is byte index %d\n", idx, byte_index);


   return 0;
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


int main() {
   char result[17]; // Ensure this has enough space for the result
   utf8_substring("🦀🦮🦮🦀🦀🦮🦮", 3, 7, result);
   printf("String: 🦀🦮🦮🦀🦀🦮🦮\nSubstring: %s\n", result); // Expected output: 🦀🦀🦮🦮
   return 0;
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


int main() {
   char str[] = "Joséph";
   int32_t idx = 4;
   printf("Codepoint at %d in %s is %d\n", idx, str, codepoint_at(str, idx)); // Output: 112
   return 0;
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
   char str[] = "Here is a mouse 🐀 and a crab 🦀.";
   int32_t idx1 = 15; // Index for 🐀
   int32_t idx2 = 25; // Index for 🦀
  
   printf("Is animal emoji at index %d? %d\n", idx1, is_animal_emoji_at(str, idx1)); // Expected: 1
   printf("Is animal emoji at index %d? %d\n", idx2, is_animal_emoji_at(str, idx2)); // Expected: 1
  
   return 0;
}
*/