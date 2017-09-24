<template>
  <div id="todo-app">
    <h1> Demo 13: 文件上传 </h1>

    <el-upload
      class="avatar-uploader"
      :action="actionUrl"
      name="photos"
      :show-file-list="false"
      :on-success="handleAvatarSuccess"
      :before-upload="beforeAvatarUpload">
      <img v-if="imageUrl" :src="imageUrl" class="avatar">
      <i v-else class="el-icon-plus avatar-uploader-icon"></i>
      
    </el-upload>

  </div>
</template>


<script>

  const BASE_URL = 'http://localhost:8080';
  //const BASE_URL = 'http://localhost:8889';
  export default {
    data() {
      return {
        actionUrl: BASE_URL+'/img/upload',
        imageUrl: ''
      };
    },
    methods: {
      handleAvatarSuccess(res, file) {
        if(res)
        {
          this.imageUrl = BASE_URL+"/"+res;
        }
        else{
          this.imageUrl = URL.createObjectURL(file.raw);
        }

      },
      beforeAvatarUpload(file) {
        const allowFormat = (file.type === 'image/jpeg'||file.type === 'image/png');
        const isLt2M = file.size / 1024 / 1024 < 2;

        console.log(file);

        if (!allowFormat) {
          this.$message.error('上传头像图片只能是 JPG&PNG 格式!');
        }
        if (!isLt2M) {
          this.$message.error('上传头像图片大小不能超过 2MB!');
        }
        return allowFormat && isLt2M;
      }
    }
  }
</script>



<style>
  .avatar-uploader .el-upload {
    border: 1px dashed #d9d9d9;
    border-radius: 6px;
    cursor: pointer;
    position: relative;
    overflow: hidden;
  }
  .avatar-uploader .el-upload:hover {
    border-color: #20a0ff;
  }
  .avatar-uploader-icon {
    font-size: 28px;
    color: #8c939d;
    width: 178px;
    height: 178px;
    line-height: 178px;
    text-align: center;
  }
  .avatar {
    width: 178px;
    height: 178px;
    display: block;
  }
</style>



