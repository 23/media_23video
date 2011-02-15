This module adds support for videos from [23 Video](http://www.23video.com) to [Embedded Media Field](http://drupal.org/project/emfield).

The `media_23video` module is a container for 23 Video's [oEmbed support](http://blog.23developer.com/2011/01/oembed/). Each input URL is simply forwarded to the oEmbed endpoint and the embed code and thumbnails are directed back to Drupal and CCK.

### Installation

This module is built for Drupal 6. 

To install the module, copy in the `media_23video` folder to `modules/` and install the *Media: 23 Video* module along with all requirements. After this, set up your domain from `/admin/settings/media_23video` to start embedding.

### Credits

The code in this module is an unholy merge of stuff from these two existing emfield modules:

* http://drupal.org/project/media_vimeo
* http://drupal.org/project/media_hulu

Maintained by [23](http://www.23video.com) and [Steffen Tiedemann Christensen](http://refresh.dk)
