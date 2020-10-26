# Load autoconfig.yml
config.load_autoconfig()

# Jblock setup
import sys, os
sys.path.append(os.path.join(sys.path[0], 'jblock'))
config.source("jblock/jblock/integrations/qutebrowser.py")

# Skip ads straight away on youtube
from qutebrowser.api import interceptor
def filter_yt(info: interceptor.Request):
    url = info.request_url
    if url.host() == 'www.youtube.com' and url.path() == '/get_video_info' and '&adformat=' in url.query():
        info.block()
interceptor.register(filter_yt)
